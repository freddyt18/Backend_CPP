#ifndef Hashing_H
#define Hashing_H

#include <openssl/des.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>
#include <string>
#include <vector>
#include <regex>


class TripleDes {
public:
    static TripleDes& getInstance() {
        static TripleDes instance;
        return instance;
    }

    std::string encrypt(const std::string& plaintext) {
        // Determine the length of the padded plaintext
        size_t padded_length = ((plaintext.size() + 7) / 8) * 8;

        // Create a vector to hold the padded plaintext
        std::vector<unsigned char> padded_plaintext(padded_length);

        // Copy the plaintext into the padded plaintext vector
        std::copy(plaintext.begin(), plaintext.end(), padded_plaintext.begin());

        // Determine the value of the padding bytes
        unsigned char padding_value = padded_length - plaintext.size();

        // Add the padding bytes to the end of the padded plaintext vector
        std::fill(padded_plaintext.begin() + plaintext.size(), padded_plaintext.end(), padding_value);

        // Create a vector to hold the ciphertext
        std::vector<unsigned char> ciphertext(padded_length);

        // Perform the encryption
        for (size_t i = 0; i < padded_length; i += 8) {
            DES_ecb3_encrypt((const_DES_cblock*)(padded_plaintext.data() + i), (DES_cblock*)(ciphertext.data() + i), &key_schedule_, &key_schedule_, &key_schedule_, DES_ENCRYPT);
        }

        // Create a memory BIO to hold the Base64 encoded data
        BIO* b64 = BIO_new(BIO_f_base64());
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
        BIO* mem = BIO_new(BIO_s_mem());
        b64 = BIO_push(b64, mem);

        // Write the ciphertext to the memory BIO
        BIO_write(b64, ciphertext.data(), ciphertext.size());
        BIO_flush(b64);

        // Get a pointer to the Base64 encoded data
        BUF_MEM* bptr;
        BIO_get_mem_ptr(b64, &bptr);

        // Create a string to hold the Base64 encoded data
        std::string encoded(bptr->data, bptr->length);

        // Free the memory BIO
        BIO_free_all(b64);

        return encoded;
    }

    std::string decrypt(const std::string& encoded) {
        // Validating the encoded string with a regex
        std::cout << "String: " << encoded << std::endl;
        std::regex base64_regex("^([A-Za-z0-9+/]{4})*([A-Za-z0-9+/]{3}=|[A-Za-z0-9+/]{2}==)?$");
        if (!std::regex_match(encoded, base64_regex)) {
            throw std::runtime_error("Invalid Base64 Encoding");
        }

        // Validating the encoded string : padding = right length
        if (encoded.size() % 4 != 0) {
            throw std::runtime_error("Incorrect padding.");
        }
        

        // Create a memory BIO to hold the Base64 encoded data
        BIO* b64 = BIO_new(BIO_f_base64());
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
        BIO* mem = BIO_new_mem_buf(encoded.data(), encoded.size());
        mem = BIO_push(b64, mem);

        // Create a vector to hold the decoded data
        std::vector<unsigned char> decoded(encoded.size());

        // Read the decoded data from the memory BIO
        int decoded_length = BIO_read(mem, decoded.data(), decoded.size());

        // Free the memory BIO
        BIO_free_all(mem);

        // Create a vector to hold the decrypted data
        std::vector<unsigned char> decrypted(decoded_length);

        // Perform the decryption
        for (size_t i = 0; i < decoded_length; i += 8) {
            DES_ecb3_encrypt((const_DES_cblock*)(decoded.data() + i), (DES_cblock*)(decrypted.data() + i), &key_schedule_, &key_schedule_, &key_schedule_, DES_DECRYPT);
        }

        // Determine the value of the padding bytes
        unsigned char padding_value = decrypted.back();

        // Determine the length of the plaintext
        size_t plaintext_length = decrypted.size() - padding_value;

        return std::string(decrypted.begin(), decrypted.begin() + plaintext_length);
    }


private:
    DES_key_schedule key_schedule_;

    TripleDes() {
        // Set the universal encryption key
        std::vector<unsigned char> key = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                                          0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10,
                                          0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18};
        DES_set_key_unchecked((const_DES_cblock*)key.data(), &key_schedule_);
    }

    // Disable copy constructor and assignment operator
    TripleDes(const TripleDes&) = delete;
    void operator=(const TripleDes&) = delete;
};


#endif
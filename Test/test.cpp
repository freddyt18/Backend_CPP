#include <iostream>
#include <string>
#include <vector>
#include "../middlewares/Hashing.h"

int main() {
    // Get a reference to the singleton instance of the TripleDes class
    TripleDes& des = TripleDes::getInstance();

    // Set the plaintext message
    std::string plaintext = "Hello, World! This is a long message that can be encrypted and decrypted using Triple DES.";

    // Encrypt the message
    std::string ciphertext = des.encrypt(plaintext);

    // Print the encrypted message
    std::cout << ciphertext << std::endl;

    // Decrypt the message
    std::string decrypted = des.decrypt(ciphertext);

    // Print the decrypted message
    std::cout << decrypted << std::endl;

    return 0;
}


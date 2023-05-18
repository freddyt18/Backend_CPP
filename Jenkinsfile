pipeline {
    agent {
        label 'main'
    }
    stages {
        stage('Create .env'){
            steps {
                sh """
                    touch .env && \\
                    echo 'HOST=${HOST}\nUSERNAME=${USERNAME}\nPASSWORD=${PASSWORD}\nDATABASE=${DATABASE}' > .env 
                """
            }
        }
        stage('Build Image') {
            steps {
                sh 'sudo docker build -t backend_cpp:latest .'
            }
        }

        stage('Containerize Image') {
            steps {
                sh 'sudo docker rm -f backend_cpp && docker run -d --name backend_cpp -p 18080:18080 -v /root/tools/vcpkg:/vcpkg backend_cpp:latest'
            }
        }
    }
}
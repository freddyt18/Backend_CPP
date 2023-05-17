pipeline {
    agent {
        label 'web'
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
                sh 'docker build -t backend_cpp:latest .'
            }
        }

        stage('Containerize Image') {
            steps {
                sh 'docker rm -f backend_cpp && docker run -d --name backend_cpp -p 18080:18080 backend_cpp:latest'
            }
        }
    }
}
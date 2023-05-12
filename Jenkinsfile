pipeline {
    agent {
        label 'Built-In'
    }
    stages {
        stage('Updating Resources') {
            steps {
                sh 'git pull origin master'
            }
        }

        stage('Build Image') {
            steps {
                sh 'docker build -t backend_cpp:latest .'
            }
        }

        stage('Containerize Image') {
            steps {
                sh 'docker rm -f backend_cpp'
                sh 'docker run -d --name backend_cpp -p 18080:18080 backend_cpp:latest'
            }
        }
    }
}
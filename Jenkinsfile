pipeline {
    agent any
    environment {
        // Set the ssh key for the mirror using secret private key
        PRIVATE_KEY = credentials('EPITECH_SSH_KEY')
        PUBLIC_KEY = credentials('EPITECH_SSH_PUBKEY')
        MIRROR_URL = 'git@github.com:EpitechPromo2027/B-OOP-400-NAN-4-1-arcade-marius.pain.git'
        BIN_NAME = 'arcade'
    }
    stages {
        stage('🔍 Checkout') {
            steps {
                // Clean before checkout
                cleanWs()

                // Clone the repository
                checkout scm
            }
        }
        stage('🕵️ Lint') {
            steps {
                // Run docker container
                sh 'docker run --rm --security-opt "label:disable" -v "$(pwd)":"/mnt/delivery" -v "$(pwd)":"/mnt/reports" ghcr.io/epitech/coding-style-checker:latest "/mnt/delivery" "/mnt/reports"'

                // Parse the report and fail the build if the quality gate is not passed
                script {
                    def report = readFile 'coding-style-reports.log'
                    def errors = report.readLines()
                    for (error in errors) {
                        def file = error.split(':')[0]
                        def line = error.split(':')[1]
                        def type = error.split(':')[2]
                        def code = error.split(':')[3]
                        echo "File: ${file}, Line: ${line}, Type: ${type}, Code: ${code}"
                    }
                    // Archive the report
                    archiveArtifacts 'coding-style-reports.log'

                    // Publish the report
                    publishHTML([allowMissing: false, alwaysLinkToLastBuild: false, keepAll: true, reportDir: '.', reportFiles: 'coding-style-reports.log', reportName: 'Coding Style Report', reportTitles: ''])

                    // Fail the build if the quality gate is not passed
                    if (errors.size() > 1) { // 1 error until it is fixed in the epitech linter
                        // If on main branch, fail the build otherwise just warn
                        if (env.BRANCH_NAME == 'main') {
                            error "Too many coding style errors"
                        }
                        else {
                            unstable "Too many coding style errors"
                        }
                    }
                }
            }
        }
        stage('🏗️ Build') {
            agent {
                docker {
                    image 'epitechcontent/epitest-docker:latest'
                    args '-v /etc/passwd:/etc/passwd:ro'
                }
            }
            steps {
                ansiColor('xterm') {
                    // Run make in the container
                    sh 'make'

                    // Check file presence (e.g. binary, library, etc.)
                    script {
                        if (!fileExists(BIN_NAME)) {
                            error "The binary file does not exist"
                        }
                        if (!fileExists('lib/arcade_ncurses.so')) {
                            error "Missing graphical library: NCurses"
                        }
                        if (!fileExists('lib/arcade_sdl2.so')) {
                            error "Missing graphical library: SDL2"
                        }
                        if (!fileExists('lib/arcade_sfml.so')) {
                            error "Missing graphical library: SFML"
                        }
                        if (!fileExists('lib/arcade_pacman.so')) {
                            error "Missing game library: Pacman"
                        }
                        if (!fileExists('lib/arcade_snake.so')) {
                            error "Missing game library: Snake"
                        }
                    }
                    // Archive the binary
                    archiveArtifacts BIN_NAME
                }
            }
        }
        stage ('🧪 Tests') {
            steps {
                ansiColor('xterm') {
                    // Run the tests
                    sh 'make tests_run'

                    // Update gcovr
                    sh 'python3 -m pip install -Iv gcovr==6.0'

                    script {
                        def dirs = ['games/Pacman', 'games/Snake', 'drivers/ncurses', 'drivers/sdl2', 'drivers/sfml']

                        for (dir in dirs) {
                            sh "cd ${dir} && gcovr --cobertura cobertura.xml --exclude tests/"
                            junit(testResults: "${dir}/criterion.xml", allowEmptyResults : true)
                            recordCoverage(tools: [[parser: 'COBERTURA']],
                                    id: "${dir}", name: "Coverage ${dir}",
                                    sourceCodeRetention: 'EVERY_BUILD')
                        }
                    }
                }
            }
        }
        stage('🪞 Mirror') {
            when {
                branch 'main'
            }
            steps {
                // Remove the mirror if it already exists
                sh "git remote remove mirror || true"

                // Add the mirror
                sh "git remote add mirror ${MIRROR_URL}"


                // Switch to the main branch
                sh "git checkout main"

                // Setup the ssh key for the mirror
                withCredentials([sshUserPrivateKey(credentialsId: 'EPITECH_SSH_KEY', keyFileVariable: 'PRIVATE_KEY')]) {
                    sh 'GIT_SSH_COMMAND="ssh -i $PRIVATE_KEY" git push --mirror mirror'
                }
            }
        }
    }
    post {
        // Clean after build
        always {
            cleanWs(cleanWhenNotBuilt: true,
                    deleteDirs: true,
                    disableDeferredWipeout: true,
                    notFailBuild: true,
                    patterns: [[pattern: '.gitignore', type: 'INCLUDE'],
                               [pattern: '.propsfile', type: 'EXCLUDE']])
            sh 'make fclean'
        }
    }
}
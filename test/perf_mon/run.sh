./appserver > server.log 2>&1 &
./appclient 127.0.0.1 9000 >> cli.log 2>&1 &

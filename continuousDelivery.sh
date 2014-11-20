while true; do
    inotifywait -e modify,delete,moved_to ./include/ --exclude \#
    make
    make run-test
done

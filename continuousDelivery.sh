while true; do
    $(inotifywait -e attrib,moved_to,create ./include)
    make
    make run-test
done

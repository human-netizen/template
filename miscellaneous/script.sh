mkdir -p contest
for dir in {a..h}; do
    mkdir -p contest/$dir
    cp solve.cpp contest/$dir/
    cp brute.cpp contest/$dir/
    cp gen.cpp contest/$dir/
    cp stress.sh contest/$dir/
    chmod +x contest/$dir/stress.sh
done

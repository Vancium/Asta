
rm compile_commands.json

cmake -S . -B bin -G "Unix Makefiles"
cd bin && make

cd ..




ln -s bin/compile_commands.json compile_commands.json

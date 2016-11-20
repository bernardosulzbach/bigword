SECONDS=0

# Create the symbolic link we need.
if [ ! -f $COMPILATION_DATABASE ]; then
  ln -s bld/compile_commands.json
fi

echo Reformatting...
clang-format -i src/*

echo "Done after $SECONDS seconds."

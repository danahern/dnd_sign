# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/danahern/code/dnd_sign

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/danahern/code/dnd_sign/build

# Utility rule file for flash.

# Include the progress variables for this target.
include CMakeFiles/flash.dir/progress.make

CMakeFiles/flash:
	cd /home/danahern/code/dnd_sign/esp-idf/components/esptool_py && /usr/bin/cmake -D IDF_PATH="/home/danahern/code/dnd_sign/esp-idf" -D SERIAL_TOOL="/home/danahern/.espressif/python_env/idf4.4_py3.9_env/bin/python /home/danahern/code/dnd_sign/esp-idf/components/esptool_py/esptool/esptool.py --chip esp32" -D SERIAL_TOOL_ARGS="--before=default_reset --after=hard_reset write_flash @flash_args" -D WORKING_DIRECTORY="/home/danahern/code/dnd_sign/build" -P /home/danahern/code/dnd_sign/esp-idf/components/esptool_py/run_serial_tool.cmake

flash: CMakeFiles/flash
flash: CMakeFiles/flash.dir/build.make

.PHONY : flash

# Rule to build all files generated by this target.
CMakeFiles/flash.dir/build: flash

.PHONY : CMakeFiles/flash.dir/build

CMakeFiles/flash.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/flash.dir/cmake_clean.cmake
.PHONY : CMakeFiles/flash.dir/clean

CMakeFiles/flash.dir/depend:
	cd /home/danahern/code/dnd_sign/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/danahern/code/dnd_sign /home/danahern/code/dnd_sign /home/danahern/code/dnd_sign/build /home/danahern/code/dnd_sign/build /home/danahern/code/dnd_sign/build/CMakeFiles/flash.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/flash.dir/depend


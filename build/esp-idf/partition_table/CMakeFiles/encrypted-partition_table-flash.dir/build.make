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

# Utility rule file for encrypted-partition_table-flash.

# Include the progress variables for this target.
include esp-idf/partition_table/CMakeFiles/encrypted-partition_table-flash.dir/progress.make

esp-idf/partition_table/CMakeFiles/encrypted-partition_table-flash:
	cd /home/danahern/code/dnd_sign/build/esp-idf/partition_table && /usr/bin/cmake -E echo "Error: The target encrypted-partition_table-flash requires"
	cd /home/danahern/code/dnd_sign/build/esp-idf/partition_table && /usr/bin/cmake -E echo "CONFIG_SECURE_FLASH_ENCRYPTION_MODE_DEVELOPMENT to be enabled."
	cd /home/danahern/code/dnd_sign/build/esp-idf/partition_table && /usr/bin/cmake -E env "FAIL_MESSAGE=Failed executing target (see errors on lines above)" /usr/bin/cmake -P /home/danahern/code/dnd_sign/esp-idf/tools/cmake/scripts/fail.cmake

encrypted-partition_table-flash: esp-idf/partition_table/CMakeFiles/encrypted-partition_table-flash
encrypted-partition_table-flash: esp-idf/partition_table/CMakeFiles/encrypted-partition_table-flash.dir/build.make

.PHONY : encrypted-partition_table-flash

# Rule to build all files generated by this target.
esp-idf/partition_table/CMakeFiles/encrypted-partition_table-flash.dir/build: encrypted-partition_table-flash

.PHONY : esp-idf/partition_table/CMakeFiles/encrypted-partition_table-flash.dir/build

esp-idf/partition_table/CMakeFiles/encrypted-partition_table-flash.dir/clean:
	cd /home/danahern/code/dnd_sign/build/esp-idf/partition_table && $(CMAKE_COMMAND) -P CMakeFiles/encrypted-partition_table-flash.dir/cmake_clean.cmake
.PHONY : esp-idf/partition_table/CMakeFiles/encrypted-partition_table-flash.dir/clean

esp-idf/partition_table/CMakeFiles/encrypted-partition_table-flash.dir/depend:
	cd /home/danahern/code/dnd_sign/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/danahern/code/dnd_sign /home/danahern/code/dnd_sign/esp-idf/components/partition_table /home/danahern/code/dnd_sign/build /home/danahern/code/dnd_sign/build/esp-idf/partition_table /home/danahern/code/dnd_sign/build/esp-idf/partition_table/CMakeFiles/encrypted-partition_table-flash.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : esp-idf/partition_table/CMakeFiles/encrypted-partition_table-flash.dir/depend

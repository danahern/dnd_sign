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
CMAKE_SOURCE_DIR = /home/danahern/code/dnd_sign/esp-idf/components/bootloader/subproject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/danahern/code/dnd_sign/build/bootloader

# Utility rule file for bootloader_check_size.

# Include the progress variables for this target.
include esp-idf/esptool_py/CMakeFiles/bootloader_check_size.dir/progress.make

esp-idf/esptool_py/CMakeFiles/bootloader_check_size:
	cd /home/danahern/code/dnd_sign/build/bootloader/esp-idf/esptool_py && /home/danahern/.espressif/python_env/idf4.4_py3.9_env/bin/python /home/danahern/code/dnd_sign/esp-idf/components/partition_table/check_sizes.py --offset 0x8000 bootloader 0x1000 /home/danahern/code/dnd_sign/build/bootloader/bootloader.bin

bootloader_check_size: esp-idf/esptool_py/CMakeFiles/bootloader_check_size
bootloader_check_size: esp-idf/esptool_py/CMakeFiles/bootloader_check_size.dir/build.make

.PHONY : bootloader_check_size

# Rule to build all files generated by this target.
esp-idf/esptool_py/CMakeFiles/bootloader_check_size.dir/build: bootloader_check_size

.PHONY : esp-idf/esptool_py/CMakeFiles/bootloader_check_size.dir/build

esp-idf/esptool_py/CMakeFiles/bootloader_check_size.dir/clean:
	cd /home/danahern/code/dnd_sign/build/bootloader/esp-idf/esptool_py && $(CMAKE_COMMAND) -P CMakeFiles/bootloader_check_size.dir/cmake_clean.cmake
.PHONY : esp-idf/esptool_py/CMakeFiles/bootloader_check_size.dir/clean

esp-idf/esptool_py/CMakeFiles/bootloader_check_size.dir/depend:
	cd /home/danahern/code/dnd_sign/build/bootloader && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/danahern/code/dnd_sign/esp-idf/components/bootloader/subproject /home/danahern/code/dnd_sign/esp-idf/components/esptool_py /home/danahern/code/dnd_sign/build/bootloader /home/danahern/code/dnd_sign/build/bootloader/esp-idf/esptool_py /home/danahern/code/dnd_sign/build/bootloader/esp-idf/esptool_py/CMakeFiles/bootloader_check_size.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : esp-idf/esptool_py/CMakeFiles/bootloader_check_size.dir/depend


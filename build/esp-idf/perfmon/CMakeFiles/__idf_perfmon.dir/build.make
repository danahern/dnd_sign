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

# Include any dependencies generated for this target.
include esp-idf/perfmon/CMakeFiles/__idf_perfmon.dir/depend.make

# Include the progress variables for this target.
include esp-idf/perfmon/CMakeFiles/__idf_perfmon.dir/progress.make

# Include the compile flags for this target's objects.
include esp-idf/perfmon/CMakeFiles/__idf_perfmon.dir/flags.make

esp-idf/perfmon/CMakeFiles/__idf_perfmon.dir/xtensa_perfmon_access.c.obj: esp-idf/perfmon/CMakeFiles/__idf_perfmon.dir/flags.make
esp-idf/perfmon/CMakeFiles/__idf_perfmon.dir/xtensa_perfmon_access.c.obj: ../esp-idf/components/perfmon/xtensa_perfmon_access.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/danahern/code/dnd_sign/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object esp-idf/perfmon/CMakeFiles/__idf_perfmon.dir/xtensa_perfmon_access.c.obj"
	cd /home/danahern/code/dnd_sign/build/esp-idf/perfmon && /home/danahern/.espressif/tools/xtensa-esp32-elf/esp-2021r1-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/__idf_perfmon.dir/xtensa_perfmon_access.c.obj   -c /home/danahern/code/dnd_sign/esp-idf/components/perfmon/xtensa_perfmon_access.c

esp-idf/perfmon/CMakeFiles/__idf_perfmon.dir/xtensa_perfmon_access.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_perfmon.dir/xtensa_perfmon_access.c.i"
	cd /home/danahern/code/dnd_sign/build/esp-idf/perfmon && /home/danahern/.espressif/tools/xtensa-esp32-elf/esp-2021r1-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/danahern/code/dnd_sign/esp-idf/components/perfmon/xtensa_perfmon_access.c > CMakeFiles/__idf_perfmon.dir/xtensa_perfmon_access.c.i

esp-idf/perfmon/CMakeFiles/__idf_perfmon.dir/xtensa_perfmon_access.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_perfmon.dir/xtensa_perfmon_access.c.s"
	cd /home/danahern/code/dnd_sign/build/esp-idf/perfmon && /home/danahern/.espressif/tools/xtensa-esp32-elf/esp-2021r1-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/danahern/code/dnd_sign/esp-idf/components/perfmon/xtensa_perfmon_access.c -o CMakeFiles/__idf_perfmon.dir/xtensa_perfmon_access.c.s

esp-idf/perfmon/CMakeFiles/__idf_perfmon.dir/xtensa_perfmon_apis.c.obj: esp-idf/perfmon/CMakeFiles/__idf_perfmon.dir/flags.make
esp-idf/perfmon/CMakeFiles/__idf_perfmon.dir/xtensa_perfmon_apis.c.obj: ../esp-idf/components/perfmon/xtensa_perfmon_apis.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/danahern/code/dnd_sign/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object esp-idf/perfmon/CMakeFiles/__idf_perfmon.dir/xtensa_perfmon_apis.c.obj"
	cd /home/danahern/code/dnd_sign/build/esp-idf/perfmon && /home/danahern/.espressif/tools/xtensa-esp32-elf/esp-2021r1-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/__idf_perfmon.dir/xtensa_perfmon_apis.c.obj   -c /home/danahern/code/dnd_sign/esp-idf/components/perfmon/xtensa_perfmon_apis.c

esp-idf/perfmon/CMakeFiles/__idf_perfmon.dir/xtensa_perfmon_apis.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_perfmon.dir/xtensa_perfmon_apis.c.i"
	cd /home/danahern/code/dnd_sign/build/esp-idf/perfmon && /home/danahern/.espressif/tools/xtensa-esp32-elf/esp-2021r1-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/danahern/code/dnd_sign/esp-idf/components/perfmon/xtensa_perfmon_apis.c > CMakeFiles/__idf_perfmon.dir/xtensa_perfmon_apis.c.i

esp-idf/perfmon/CMakeFiles/__idf_perfmon.dir/xtensa_perfmon_apis.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_perfmon.dir/xtensa_perfmon_apis.c.s"
	cd /home/danahern/code/dnd_sign/build/esp-idf/perfmon && /home/danahern/.espressif/tools/xtensa-esp32-elf/esp-2021r1-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/danahern/code/dnd_sign/esp-idf/components/perfmon/xtensa_perfmon_apis.c -o CMakeFiles/__idf_perfmon.dir/xtensa_perfmon_apis.c.s

esp-idf/perfmon/CMakeFiles/__idf_perfmon.dir/xtensa_perfmon_masks.c.obj: esp-idf/perfmon/CMakeFiles/__idf_perfmon.dir/flags.make
esp-idf/perfmon/CMakeFiles/__idf_perfmon.dir/xtensa_perfmon_masks.c.obj: ../esp-idf/components/perfmon/xtensa_perfmon_masks.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/danahern/code/dnd_sign/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object esp-idf/perfmon/CMakeFiles/__idf_perfmon.dir/xtensa_perfmon_masks.c.obj"
	cd /home/danahern/code/dnd_sign/build/esp-idf/perfmon && /home/danahern/.espressif/tools/xtensa-esp32-elf/esp-2021r1-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/__idf_perfmon.dir/xtensa_perfmon_masks.c.obj   -c /home/danahern/code/dnd_sign/esp-idf/components/perfmon/xtensa_perfmon_masks.c

esp-idf/perfmon/CMakeFiles/__idf_perfmon.dir/xtensa_perfmon_masks.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_perfmon.dir/xtensa_perfmon_masks.c.i"
	cd /home/danahern/code/dnd_sign/build/esp-idf/perfmon && /home/danahern/.espressif/tools/xtensa-esp32-elf/esp-2021r1-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/danahern/code/dnd_sign/esp-idf/components/perfmon/xtensa_perfmon_masks.c > CMakeFiles/__idf_perfmon.dir/xtensa_perfmon_masks.c.i

esp-idf/perfmon/CMakeFiles/__idf_perfmon.dir/xtensa_perfmon_masks.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_perfmon.dir/xtensa_perfmon_masks.c.s"
	cd /home/danahern/code/dnd_sign/build/esp-idf/perfmon && /home/danahern/.espressif/tools/xtensa-esp32-elf/esp-2021r1-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/danahern/code/dnd_sign/esp-idf/components/perfmon/xtensa_perfmon_masks.c -o CMakeFiles/__idf_perfmon.dir/xtensa_perfmon_masks.c.s

# Object files for target __idf_perfmon
__idf_perfmon_OBJECTS = \
"CMakeFiles/__idf_perfmon.dir/xtensa_perfmon_access.c.obj" \
"CMakeFiles/__idf_perfmon.dir/xtensa_perfmon_apis.c.obj" \
"CMakeFiles/__idf_perfmon.dir/xtensa_perfmon_masks.c.obj"

# External object files for target __idf_perfmon
__idf_perfmon_EXTERNAL_OBJECTS =

esp-idf/perfmon/libperfmon.a: esp-idf/perfmon/CMakeFiles/__idf_perfmon.dir/xtensa_perfmon_access.c.obj
esp-idf/perfmon/libperfmon.a: esp-idf/perfmon/CMakeFiles/__idf_perfmon.dir/xtensa_perfmon_apis.c.obj
esp-idf/perfmon/libperfmon.a: esp-idf/perfmon/CMakeFiles/__idf_perfmon.dir/xtensa_perfmon_masks.c.obj
esp-idf/perfmon/libperfmon.a: esp-idf/perfmon/CMakeFiles/__idf_perfmon.dir/build.make
esp-idf/perfmon/libperfmon.a: esp-idf/perfmon/CMakeFiles/__idf_perfmon.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/danahern/code/dnd_sign/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C static library libperfmon.a"
	cd /home/danahern/code/dnd_sign/build/esp-idf/perfmon && $(CMAKE_COMMAND) -P CMakeFiles/__idf_perfmon.dir/cmake_clean_target.cmake
	cd /home/danahern/code/dnd_sign/build/esp-idf/perfmon && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/__idf_perfmon.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
esp-idf/perfmon/CMakeFiles/__idf_perfmon.dir/build: esp-idf/perfmon/libperfmon.a

.PHONY : esp-idf/perfmon/CMakeFiles/__idf_perfmon.dir/build

esp-idf/perfmon/CMakeFiles/__idf_perfmon.dir/clean:
	cd /home/danahern/code/dnd_sign/build/esp-idf/perfmon && $(CMAKE_COMMAND) -P CMakeFiles/__idf_perfmon.dir/cmake_clean.cmake
.PHONY : esp-idf/perfmon/CMakeFiles/__idf_perfmon.dir/clean

esp-idf/perfmon/CMakeFiles/__idf_perfmon.dir/depend:
	cd /home/danahern/code/dnd_sign/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/danahern/code/dnd_sign /home/danahern/code/dnd_sign/esp-idf/components/perfmon /home/danahern/code/dnd_sign/build /home/danahern/code/dnd_sign/build/esp-idf/perfmon /home/danahern/code/dnd_sign/build/esp-idf/perfmon/CMakeFiles/__idf_perfmon.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : esp-idf/perfmon/CMakeFiles/__idf_perfmon.dir/depend

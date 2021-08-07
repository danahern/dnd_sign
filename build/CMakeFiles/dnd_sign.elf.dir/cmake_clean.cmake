file(REMOVE_RECURSE
  "bootloader/bootloader.bin"
  "bootloader/bootloader.elf"
  "bootloader/bootloader.map"
  "config/sdkconfig.cmake"
  "config/sdkconfig.h"
  "dnd_sign.bin"
  "dnd_sign.map"
  "flash_project_args"
  "project_elf_src_esp32.c"
  "CMakeFiles/dnd_sign.elf.dir/project_elf_src_esp32.c.obj"
  "dnd_sign.elf"
  "dnd_sign.elf.pdb"
  "project_elf_src_esp32.c"
)

# Per-language clean rules from dependency scanning.
foreach(lang C)
  include(CMakeFiles/dnd_sign.elf.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()

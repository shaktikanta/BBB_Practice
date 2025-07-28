cmd_/mnt/d/BBB_practice/test_driver/modules.order := {   echo /mnt/d/BBB_practice/test_driver/testDriver.ko; :; } | awk '!x[$$0]++' - > /mnt/d/BBB_practice/test_driver/modules.order

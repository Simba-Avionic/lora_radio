To use the definied messages you need to build them first and then source them (tell your operating system where those exist).

build the messages:
* cd lora_ros_msgs
* colcon build

the building process will create a "install" dir
now to use the messages you need to source a script generated during the build process, the script location is (place of building)/install/local_setup.sh

source the messages:
* cd lora_ros_msgs
* source install/local_setup.sh

the source process has to be done every single time you want to use the messages
the source is preserved during entire terminal session - no need to source every second command
just open the terminal, source, use

you can put the source command in your ~/.bashrc file (at the end) - this will result in automatic sourcing the messages for every new terminal you open
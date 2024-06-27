#!/bin/bash

create_xv6() {
    docker run -it --name xv6 --hostname xv6 -v /home/shuaikai/project/labs/xv6-2020:/home/shuaikai/xv6-2020 -w /home/shuaikai/xv6-2020 xv6-ubuntu20 bash
}
xv6(){
    docker start xv6 && docker exec -it xv6 bash
}
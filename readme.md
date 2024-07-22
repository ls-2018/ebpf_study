```

if [ "$ARCH" == "amd64" ];then
cat > /etc/apt/sources.list << EOF
deb http://mirrors.huaweicloud.com/repository/ubuntu/ jammy main restricted
deb http://mirrors.huaweicloud.com/repository/ubuntu/ jammy-updates main restricted
deb http://mirrors.huaweicloud.com/repository/ubuntu/ jammy universe
deb http://mirrors.huaweicloud.com/repository/ubuntu/ jammy-updates universe
deb http://mirrors.huaweicloud.com/repository/ubuntu/ jammy multiverse
deb http://mirrors.huaweicloud.com/repository/ubuntu/ jammy-updates multiverse
deb http://mirrors.huaweicloud.com/repository/ubuntu/ jammy-backports main restricted universe multiverse
deb http://mirrors.huaweicloud.com/repository/ubuntu/ jammy-security main restricted
deb http://mirrors.huaweicloud.com/repository/ubuntu/ jammy-security universe
deb http://mirrors.huaweicloud.com/repository/ubuntu/ jammy-security multiverse
EOF
fi

if [ "$ARCH" == "arm64" ];then
cat > /etc/apt/sources.list << EOF
deb http://repo.huaweicloud.com/ubuntu-ports/ jammy main restricted universe multiverse
deb http://repo.huaweicloud.com/ubuntu-ports/ jammy-security main restricted universe multiverse
deb http://repo.huaweicloud.com/ubuntu-ports/ jammy-updates main restricted universe multiverse
deb http://repo.huaweicloud.com/ubuntu-ports/ jammy-backports main restricted universe multiverse
EOF
fi



```
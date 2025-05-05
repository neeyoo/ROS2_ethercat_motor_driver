FROM arm64v8/ros:humble

# Set noninteractive mode for apt-get
ENV DEBIAN_FRONTEND=noninteractive

# Set up user yang
ARG USERNAME=yang
ARG UID=1000
ARG GID=1000

RUN apt-get update \
    && apt-get install -y \
    bash-completion \
    cmake \
    curl \
    git \
    python3-colcon-common-extensions \
    python3-vcstool \
    wget \
    python3-pip \
    libwebsocketpp-dev \
    clang lldb lld \
    && pip3 install flask-socketio fastapi uvicorn \
    && update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++ 100 \
    && rm -rf /var/lib/apt/lists/*

# Install necessary ROS 2 packages
RUN apt-get update && apt-get install -y \
    ros-humble-navigation2 \
    ros-humble-nav2-bringup \
    ros-humble-moveit \
    ros-humble-moveit-ros-planning-interface \
    && rm -rf /var/lib/apt/lists/*

# setup keys
RUN apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys D2486D2DD83DB69272AFE98867170598AF249743

# setup sources.list
RUN . /etc/os-release \
    && echo "deb http://packages.osrfoundation.org/gazebo/$ID-stable `lsb_release -sc` main" > /etc/apt/sources.list.d/gazebo-latest.list

# Create and switch to user
RUN groupadd -g $GID $USERNAME \
    && useradd -lm -u $UID -g $USERNAME -s /bin/bash $USERNAME \
    && echo "$USERNAME ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers
USER $USERNAME

# Create workspace so that user own this directory
RUN mkdir -p /home/$USERNAME/ros2_ws/src
WORKDIR /home/$USERNAME/ros2_ws

# Set up environment
RUN echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc

CMD ["bash"]


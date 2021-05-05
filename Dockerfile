FROM ubuntu
COPY Synctime /Synctime
WORKDIR /Synctime/
ENV TZ 'Asia/Singapore'
RUN echo $TZ > /etc/timezone && \ 
    apt-get update && \
    apt-get -y install gcc mono-mcs && \ 
    apt-get install -y tzdata && \ 
    rm /etc/localtime && \ 
    ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && \
    dpkg-reconfigure -f noninteractive tzdata && \ 
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*
RUN gcc -o synctime num_hex.c num_hex.h serial_config.c serial_config.h synctime.c
CMD ["./synctime"]

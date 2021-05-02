FROM ubuntu
COPY Synctime /Synctime
WORKDIR /Synctime/
RUN apt-get update && \
    apt-get -y install gcc mono-mcs && \
    rm -rf /var/lib/apt/lists/*
RUN gcc -o synctime num_hex.c num_hex.h serial_config.c serial_config.h synctime.c
CMD ["./synctime"]

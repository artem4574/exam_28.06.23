FROM ubuntu:18.04

LABEL auth="Savrasov_Artem_221_351"

ENV TZ=Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
RUN apt-get update && \
    apt-get install -y qt5-default qtbase5-dev qt5-qmake build-essential

WORKDIR /221-351_Savrasov_Artem
COPY . .
RUN qmake mySer.pro&&make
CMD ["./mySer","param"]



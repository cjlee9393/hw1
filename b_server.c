// Server는 client 와 connection establish를 한 다음, 5초 동안 sleep

// 최대 buffer 크기가 5 바이트인 버퍼를 이용하여 읽은 다음

// 읽은 데이터를 화면에 출력시킴. (recv() 이용하여 데이터 읽음.)

// 동일한 형태로 수신한 데이터를 읽어서 화면에 출력하는 동작을 반복함.

// Client가 종료되면 server도 종료시킴.
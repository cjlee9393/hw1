
// client에서는 10 바이트 데이터 3개를 server에 전송 (예를 들면 0123456789, ABCDEFGHIJ, KLMNOPQRST)

// 3번의 sendto() 함수 이용하여 전송

// 터미널로부터 입력된 데이터를 server에 전송함. 

// Client가 종료되면 server도 종료
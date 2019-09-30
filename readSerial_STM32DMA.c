//STM32のUARTをDMAで受信しArudinoのSerialライブラリのように使うやつ

//本サンプルコードはUART2で作成しているため別の番号のUARTを使う場合は適時UARTのハンドラの番号を変更してください

//バッファー宣言
//バッファの宣言はDMA開始コマンドの前に入れてください
//本来は変数宣言箇所で宣言すべきですが、他ファイルでデータ読み取りを行う場合を考慮し
///* USER CODE BEGIN Includes */と/* USER CODE END Includes */内のincludeファイル呼び出し前が良いでしょう
/* USER CODE BEGIN Includes */
#define DATANUM 100
uint8_t serialData[DATANUM] = {};
//#include "***.c"
/* USER CODE END Includes */

//DMA開始コマンド
//以下の1行はループ処理が始まる前に入れてください
//基本的には以下のようにUSER CODE BEGIN 2とUSER CODE END 2の間に入れると良いでしょう
//場所を間違えるとCubeMxの設定変更時に消えてしまいます。

  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_DMA(&huart2,serialData,DATANUM);
  /* USER CODE END 2 */

//以下コードはcubeMxの吐き出したmain.cの/* USER CODE BEGIN 0 */と/* USER CODE END 0 */の間あるいは、別のファイルに入れる必要があります。
//場所を間違えるとCubeMxの設定変更時に消えてしまいます。


//未読データ数確認関数
//返り値は未読データ数
int readDataNum(){//受信済みデータ数確認
	int index = huart2.hdmarx->Instance->NDTR; //index取得

	index = DATANUM - index;//受信データの先頭位置

	int remainData = index - indexRead;//読み込んでいないデータの数
	if(remainData < 0) remainData += DATANUM;
	return remainData;
}


//受信データ1byte受信関数
//実行ごとに古いデータから読みだされる
//返り値は受信データ
uint8_t readSerial(){//データ受信
	uint8_t readData = 0;
	
	int index = huart2.hdmarx->Instance->NDTR; //index取得
	index = DATANUM - index;

	int remainData = index - indexRead;//読み込んでいないデータの数
	if(remainData < 0) remainData += DATANUM;

	if(remainData > 0){
		readData = serialData[indexRead];
		indexRead++;
		if(indexRead == DATANUM) indexRead = 0;
	}
	
	return readData;
}

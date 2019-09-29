//STM32��UART��DMA�Ŏ�M��Arudino��Serial���C�u�����̂悤�Ɏg�����

//�{�T���v���R�[�h��UART2�ō쐬���Ă��邽�ߕʂ̔ԍ���UART���g���ꍇ�͓K��UART�̃n���h���̔ԍ���ύX���Ă�������

//DMA�J�n�R�}���h
//�ȉ���1�s�̓��[�v�������n�܂�O�ɓ���Ă�������
//��{�I�ɂ͈ȉ��̂悤��USER CODE BEGIN 2��USER CODE END 2�̊Ԃɓ����Ɨǂ��ł��傤

  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_DMA(&huart2,serialData,DATANUM);
  /* USER CODE END 2 */


//���ǃf�[�^���m�F�֐�
//�Ԃ�l�͖��ǃf�[�^��
int readDataNum(){//��M�ς݃f�[�^���m�F
	int index = huart2.hdmarx->Instance->NDTR; //index�擾

	index = DATANUM - index;//��M�f�[�^�̐擪�ʒu

	int remainData = index - indexRead;//�ǂݍ���ł��Ȃ��f�[�^�̐�
	if(remainData < 0) remainData += DATANUM;
	return remainData;
}


//��M�f�[�^1byte��M�֐�
//���s���ƂɌÂ��f�[�^����ǂ݂������
//�Ԃ�l�͎�M�f�[�^
uint8_t readSerial(){//�f�[�^��M
	uint8_t readData = 0;
	
	int index = huart2.hdmarx->Instance->NDTR; //index�擾
	index = DATANUM - index;

	int remainData = index - indexRead;//�ǂݍ���ł��Ȃ��f�[�^�̐�
	if(remainData < 0) remainData += DATANUM;

	if(remainData > 0){
		readData = serialData[indexRead];
		indexRead++;
		if(indexRead == DATANUM) indexRead = 0;
	}
	
	return readData;
}
# Project-SmartHandyFan
Cortex-M3 Mini 보드를 기반으로 한 펌웨어 프로그래밍 프로젝트


![image](https://github.com/user-attachments/assets/c417e08b-1c3d-4f29-8746-1d6522df74ea)  ![image](https://github.com/user-attachments/assets/48aac9e2-0d55-4e4b-ae36-de35c5add497)


## ⚙️ 사용 기술 (Tech Stack)

<p align="center">
  <img src="https://img.shields.io/badge/STM32-Cortex--M3-03234B?style=for-the-badge&logo=stmicroelectronics&logoColor=white"/>
  <img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white"/>
  <img src="https://img.shields.io/badge/PWM-Control-FF6F00?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/UART-Communication-007396?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/TeraTerm-Serial%20Terminal-009688?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/Interrupts-External%20Buttons-607D8B?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/L293D-Motor%20Driver-E91E63?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/CP2102-USB--UART-3F51B5?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/Logic%20Analyzer-Signal%20Test-795548?style=for-the-badge"/>
</p>


## 1. 프로젝트 개요
**본 프로젝트는 버튼 조작을 통해 손으로 들고 다닐 수 있는 작은 선풍기(핸디팬)를 제작하는 것을 목표로 하였습니다. 사용자가 다양한 모드를 선택할 수 있도록 하여 바람의 세기를 조절하고, LED로 시각적으로 표시하며, 조도센서를 이용한 자동 제어도 가능하게 구현하였습니다.**

## 2.시스템 구성

### ●구성 요소	설명
Cortex-M3 MINI 보드	펌웨어 프로그래밍을 위한 메인 보드

L293 논리 IC	모터의 방향 제어(양방향 동작)

CP2102	USB to UART 변환기, 보드 전원 공급

LED 기판 (10개)	선풍기 회전 세기를 시각적으로 표시

조도 센서	주변 밝기에 따라 회전 속도 자동 조절

버튼 2개	모드 변경 기능 수행

로직 아날라이저 & Logic 2.4.13	PWM 주파수 분석을 위한 도구

## 3.펌웨어 및 동작 원리
### ●펌웨어 프로그래밍

PC에서 테라텀(Tera Term)을 사용하여 빌드된 펌웨어를 업로드

테라텀 터미널에서 명령 입력을 통해 선풍기 제어 가능

### ●기본 모드

숫자 1~9 입력 시, 숫자 크기에 비례하여 회전 속도 증가

조도 센서(CDs) 모드

버튼 1을 누르면 진입

주변 밝기가 어두워질수록 회전 속도 감소

다시 버튼 1을 누르면 기본 모드로 복귀

### ●자동 모드

기본 모드에서 버튼 2를 누르면 진입

회전 속도가 자동으로 느려지고 빨라지기를 반복

### ●기타 명령

s 입력: 정지 모드

f 입력: 시계 방향 회전

r 입력: 반시계 방향 회전

### ●PWM 제어

회전 속도는 PWM의 듀티 비율 조절을 통해 구현

로직 아날라이저와 Logic 2.4.13을 활용하여 실제 주파수 분석 후 적절한 PWM 설정

### ●모터 방향 제어

L293 논리 IC 사용

시계 방향: 타이머2의 3채널 가동

반시계 방향: 타이머2의 4채널 가동

### ●LED 표시

회전 세기 정보를 기반으로 LED 기판의 LED 개수 점등

## 4. 문제 해결 경험
### ●초기 문제점

PWM에 대한 이해 부족으로 주파수를 직접 변경하여 회전 세기를 제어하려 했으나, 예상과 다른 동작 발생

### ●해결 과정

PWM의 개념 및 듀티 비에 대한 학습을 통해 정확한 방식으로 제어 구현

듀티 비 조절을 통해 회전 속도를 안정적으로 조절하는 데 성공

## 5. 프로젝트 결과 및 배운 점
처음으로 펌웨어를 프로그래밍하여 하드웨어 제어를 성공적으로 구현

PWM의 개념을 실전에서 정확히 이해하고 활용하게 됨

인터럽트를 활용한 버튼 제어를 통해 MCU의 효율적인 제어 방식 습득

센서, 모터, LED, PWM, 인터럽트 등 임베디드 시스템 구성 요소 간의 연동 경험

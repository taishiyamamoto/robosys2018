## robosys2018

山本大志
2018年12月27日　千葉工業大学

# 課題1について

## やったこと
ロボットシステム学の講義で用いられたLEDを光らせるプログラムを参考にして、７セグメントLEDの数字を表示するデバイスドライバを作成しました。
動画のURL：https://youtu.be/ZYvpynk3qc0

## 使用したもの
* Raspberry Pi Model 3B+
* 7セグメントLED（カソードコモン）
* 300Ω程度の電流制限抵抗

## ラズパイの環境構築
* 使用OSはraspbian、イメージファイルはNOOBSのものを使用しました。
　https://www.raspberrypi.org/downloads/noobs/
 
* 以下のシェルスクリプトを用いてカーネルの再構築を行いました。
　https://github.com/ryuichiueda/raspberry_pi_kernel_build_scripts.git

## 参考にしたプログラム
* ロボットシステム学第８回講義で扱ったLEDをGPIOピンで制御するデバイスドライバを参考にしました。
https://github.com/ryuichiueda/robosys_device_drivers.git



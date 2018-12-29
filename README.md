# ロボットシステム学課題概要

山本大志　千葉工業大学

# 課題1について

## やったこと
ロボットシステム学の講義で用いられたLEDを光らせるプログラムを参考にして、７セグメントLEDの数字を表示するデバイスドライバを作成しました。
* 動画のURL：https://youtu.be/ZYvpynk3qc0

## 使用したもの
* Raspberry Pi Model 3B+
* 7セグメントLED（カソードコモン）
* 300Ω程度の電流制限抵抗

## ラズパイの環境構築
* 使用OSはraspbian、イメージファイルは下記サイトのものを使用しました。
　https://www.raspberrypi.org/downloads/noobs/
 
* 以下のシェルスクリプトを用いてカーネルの再構築を行いました。
　https://github.com/ryuichiueda/raspberry_pi_kernel_build_scripts.git

## 参考文献
* ロボットシステム学第８回講義で扱ったLEDをGPIOピンで制御するデバイスドライバを参考にしました。
https://github.com/ryuichiueda/robosys_device_drivers.git  

* Raspberry Piのアドレスマップは以下の文献を参考にしました。
https://www.raspberrypi.org/app/uploads/2012/02/BCM2835-ARM-Peripherals.pdf

## 回路構成
![image](https://github.com/taishiyamamoto/robosys2018/blob/master/7led.png)

## プログラムの使用方法
* 動作確認
```
$ make                          #プログラムのコンパイル
$ sudo insmod myled.ko          #デバイスドライバのインストール 
$ sudo chmod 666 /dev/myled0  
$ echo 0 > /dev/myled0          #0を表示 0~9に対応  
$ echo c > /dev/myled0          #消灯
```
* 削除する場合
```
$ sudo rmmod myled
$ make clean
```

## 課題
* プログラム内部ではレジスタをマジックナンバーで直接叩いているので、編集が困難であるということ。
* Raspberry Pi 3B+ではGPIOピンに合計50mA以上の電流を出力させると動作の保障がされないため、７セグメントデコーダ等を用いて省電力化する。

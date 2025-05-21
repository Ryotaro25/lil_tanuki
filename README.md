# lil_tanuki
将棋AI開発
RocketTanukiを参考にしながらC++で将棋AIの開発を行います

## 参照コード
https://github.com/nodchip/RocketTanuki

## C++コーディングガイド
主にこちらのガイドに沿ってコーディングをします。
https://google.github.io/styleguide/cppguide.html

## 将棋ルール
https://www.shogi.or.jp/knowledge/

## UI
ShogiHomeを用いています。
https://sunfish-shogi.github.io/shogihome/

## 思考エンジン
https://github.com/yaneurao/YaneuraOu

## 各ファイルの説明
direction.h direction.cpp 各駒の動きを定義
evaluator.h 駒ごとの点数と盤面の状況から評価を行う
move_generator.h movegenerator.cpp 有効な動作を定義
piece.h piece.cpp 駒の種類や手番、駒に関する関数群を定義
position.h position.cpp 盤面上のデータを定義
searcher.h searcher.cpp mini-max法を定義
usi.h usi.cpp usiプロトコルを用いて通信するための定義

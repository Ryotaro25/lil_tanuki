# コンパイラの設定
CXX = g++
# コンパイルオプション
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I/Library/Developer/CommandLineTools/SDKs/MacOSX15.2.sdk/usr/include/c++/v1/

# 実行ファイル名
TARGET = LilTanuki
SRC = src/main.cpp src/usi.cc src/position.cpp src/piece.cpp src/utils/types.cpp src/move.cpp src/direction.cpp src/move_generator.cpp
HDR = src/usi.h src/position.h src/piece.h src/utils/types.h src/move.h src/direction.h src/move_generator.h

# オブジェクトファイル（.o）の名前
OBJ = $(SRC:.cc=.o)

# デフォルトターゲット：実行ファイルを作成
all: $(TARGET)

# 実行ファイルを作成するルール
$(TARGET): $(OBJ)
	# オブジェクトファイルから実行ファイルを作成
	$(CXX) $(CXXFLAGS) -o $@ $^

# .cc から .o を作成するルール
%.o: %.cc $(HDR)
	# ソースコードをコンパイルしてオブジェクトファイルを生成
	$(CXX) $(CXXFLAGS) -c $< -o $@

# クリーンアップターゲット：コンパイル生成物を削除
clean:
	# コンパイルで生成されたオブジェクトファイルと実行ファイルを削除
	rm -f $(OBJ) $(TARGET)

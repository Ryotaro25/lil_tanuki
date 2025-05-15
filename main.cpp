#include <iostream>
#include <string>

int main() {
  std::string ling;
  while (std::getline(std::cin, line)) {
    switch (line) {
      case "usi":
        std::cout << "id name Rocker Tanuki" << std::endl;
        std::cout << "id author nodchip" << std::endl;
        // usiコマンドを受信した時に最後に送り返すコマンドです。
        // 将棋所ではこれを返さないエンジンはUSIエンジンと認識されず
        // 登録できないので、必ず送り返す必要があります。
        std::cout << "usiok"
        break;
      case "isready":
        std::cout << "readyok" << std::endl;
        break;
      case "go":
        // GUIに投了を伝える
        std::cout << "bestmove resign" << std::endl;
        break;
      case "usinewgame":
      case "setoption":
      case "position":
      case "stop":
      case "ponderhit":
      case "gameover":
        break;
      case "quit":
        
      default:
        std::cout << "Invalid value in switch statement: " << line << std::endl;
        break;
    }
    std::cout.flush();
  }
  return 0;
}

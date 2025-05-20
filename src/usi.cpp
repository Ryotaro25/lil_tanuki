#include <chrono>
#include <iostream>

#include <sstream>
#include <string>
#include <vector>

#include "evaluator.h"
#include "move_generator.h"
#include "move.h"
#include "position.h"
#include "searcher.h"
#include "usi.h"

const std::string USI_PONDER = "USI_Ponder";
const std::string USI_HASH = "USI_Hash";

void RunUsi() {
  Position position;
  std::string line;
  while (std::getline(std::cin, line)) {
    // if (line.empty()) {
    //   continue;
    // }

    std::istringstream iss(line);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token) {
      tokens.push_back(token);
    }

    if (tokens.empty()) {
      continue;
    }

    std::string command = tokens[0];
    if (command == "usi") {
      std::cout << "id name Rocket Tanuki" << std::endl;
      std::cout << "id author nodchip" << std::endl;
      std::cout << "option name " << USI_PONDER << " type check default true" << std::endl;
      std::cout << "option name " << USI_HASH << " type spin default 256" << std::endl;
      // usiコマンドを受信した時に最後に送り返すコマンドです。
      // 将棋所ではこれを返さないエンジンはUSIエンジンと認識されず
      // 登録できないので、必ず送り返す必要があります。
      std::cout << "usiok" << std::endl;
    } else if (command == "isready") {
      std::cout << "readyok" << std::endl;
    } else if (command == "go") {
      int depth = 3;
      auto begin_time = std::chrono::steady_clock::now();
      int nodes = 0;
      BestMove best_move = Searcher::Search(position, depth, nodes);
      auto end_time = std::chrono::steady_clock::now();

      int time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - begin_time).count();
      double elapsed_seconds = std::chrono::duration<double>(end_time - begin_time).count();
      int nps = (int)(nodes / (elapsed_seconds > 0.0 ? elapsed_seconds : 1.0));

      std::string best_move_string = best_move.move.ToUsiString(); // ToUsiString() を実装しておく必要あり
      int score_cp = best_move.value;

      std::cout << "info depth " << depth
                << " seldepth " << depth
                << " time " << time
                << " nodes " << nodes
                << " score cp " << score_cp
                << " nps " << nps
                << " pv " << best_move_string << std::endl;

      if (best_move.value < -30000) {
          std::cout << "bestmove resign" << std::endl;
      } else {
          std::cout << "bestmove " << best_move_string << std::endl;
      }
      // std::vector<Move> moves = MoveGenerator::GenerateMoves(position);
      // if (moves.empty()) {
      //   std::cout << "bestmove resign" << std::endl;
      // } else {
      //   // https://cpprefjp.github.io/reference/random/random_device.html
      //   // Random クラスを用いてランダムに指し手を選択
      //   std::random_device rd;
      //   std::mt19937 gen(rd());
      //   std::uniform_int_distribution<> dist(0, moves.size() - 1);
      //   Move move = moves[dist(gen)];
      //   std::cout << "bestmove " << move.ToUsiString() << std::endl;
      // }
      
    } else if (command == "usinewgame" ||
               command == "setoption" ||
               command == "stop" ||
               command == "ponderhit" ||
               command == "gameover") {
      // 現時点では何もしません。
    } else if (command == "quit") {
      return;
    } else if (command == "d") {
      std::cout << position << std::endl;
    } else if (command == "position") {
      if (tokens.size() >= 2) {
        size_t next_index = 0;
        if (tokens[1] == "sfen") {
          std::ostringstream oss;
          oss << tokens[2] << " " << tokens[3] << " " << tokens[4] << " " << tokens[5];
          position.Set(oss.str());
          next_index = 6;
        } else if (tokens[1] == "startpos") {
          position.Set(Position::StartposSfen);
          next_index = 2;
        } else {
          std::cerr << "info string Invalid position command: " << line << std::endl;
        }

        for (size_t i = next_index; i < tokens.size(); ++i) {
          if (tokens[i] == "moves") continue;
          Move move = Move::FromUsiString(position, tokens[i]);
          position.DoMove(move);
        }
      }
    } else if (command == "generatemove") {
      for (const auto& move : MoveGenerator::GenerateMoves(position)) {
        std::cout << move << " ";
      }
      std::cout << std::endl;
    } else if (command == "eval") {
      std::cout << Evaluator::Evaluate(position) << std::endl;
    } else {
      std::cout << "info string Invalid command received: " << command << std::endl;
    }
    std::cout.flush();
  }
}

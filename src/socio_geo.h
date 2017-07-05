#ifndef SOCIO_GEO_H_
#define SOCIO_GEO_H_
#include <map>
#include <vector>
#include <list>
#include <functional>
#include <unordered_set>
#include <unordered_map>
#include <random>

namespace socio {

const int BOARD_SZ = 5e3 + 10;
const int ROW_SZ = 5e3 + 10;
const int MAXNODE = 1e3 + 10;
const int BUFFER_SZ = 20;
const int alpha = 3;

class Message {
 public:
  Message() = default;
  ~Message() = default;
  int seq, src, dst; 
  int cnt;
  Message(int, int, int, int);
};

class Node {
 public:
  Node() = default;
  Node(int sid, int tot_node_num, int places_cnt);
  void Init(int tot_node_num, int places_cnt);
  void AddMsg(int seq, int num, int src=-1, int dst=-1);
  void RemoveMsg(int seq, int num);
  void Encounter(Node* enc_node);
  std::pair<int, int> NextPosition();
  bool HasMsg(int seq);

  inline double& EnPr(int enc_node) { return enc_pr_[enc_node];} 
  inline int& EnCount(int enc_node) { return enc_count_[enc_node];}
  inline int& Sid() { return sid_;}
  inline int& BufferSize() { return buf_sz_;}
  inline int& xp() { return xp_;}
  inline int& yp() { return yp_;}
  inline int& Stat() { return stat_;}
  inline std::vector<std::pair<int, int> >& Places() { return places_;}
  inline std::pair<int, int> CurPosition() { return std::make_pair(xp(), yp());}
 private:
  std::vector<std::pair<int, int> > places_; 
  void Forward(std::pair<int, Message*>, Node*);
  int sid_, xp_, yp_, current_dst_idx_;
  std::map<int, Message*> seq2msg_;
  int buf_sz_, stat_;
  std::vector<double> enc_pr_;
  std::vector<int> enc_count_;
  std::random_device rd_;     
  std::mt19937 generator_;
  std::uniform_int_distribution<int> uni_;
};
  
class Graph {
 public:
  Graph() = default;
  ~Graph() = default;
  void Run(int cnt);
  void Init();
    
 private:
  int64_t TwoDim2One(const std::pair<int, int>&);
  void move(Node* o);
  std::vector<Node*> nodes_;
  std::unordered_map<int64_t, std::unordered_set<Node*>> pos2nodes_;
};

}

#endif

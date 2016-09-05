#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <map>
#include <memory>
#include <iterator>
#include <algorithm>
#include <queue>
#include <functional>


using namespace std;


class MyPath {
  public:
    MyPath(const string *a)
    {
        m_path.push_back(a);
    }
    MyPath(const MyPath &copy)
    {
        m_path.insert(m_path.end(), copy.begin(), copy.end());
    }
  public:
    void push_back(const string *a)
    {
        m_path.push_back(a);
    }

    int size()
    {
        return m_path.size();
    }

    const string * back() const
    {
        return m_path.back();
    }

    vector<string> get_vector()
    {
        vector<string> result;
        for (int i = 0; i < m_path.size(); i++)
        {
            result.push_back(*(m_path[i]));
        }
        return result;
    }

    void print()
    {
//        return;
        for(int i = 0; i < m_path.size(); i++)
        {
            cout << *(m_path[i]) << ' ';
        }
        cout << endl;
    }

    vector<const string *>::const_iterator begin() const
    {
        return m_path.begin();
    }

    vector<const string *>::const_iterator end() const
    {
        return m_path.end();
    }

  private:
    vector<const string *>  m_path;
};


class MyMap {
  public:
    MyMap(const string &beginWord, const string &endWord, unordered_set<string> &wordList)
    {
        for (unordered_set<string>::iterator it = wordList.begin();
             it != wordList.end();
             it = next(it))
        {
            this->word_list.insert(*it);
        }
        this->word_list.insert(beginWord);
        this->word_list.insert(endWord);

        for (unordered_set<string>::const_iterator it = this->word_list.begin();
             it != this->word_list.end();
             it = next(it))
        {
            this->adjacencies[&(*it)];
        }

        for (unordered_set<string>::const_iterator iter1 = this->word_list.begin();
             iter1 != wordList.end();
             iter1 = next(iter1))
        {
            for (unordered_set<string>::const_iterator iter2 = this->word_list.begin();
                 iter2 != wordList.end();
                 iter2 = next(iter2))
            {
                if (this->can_adjacent(*iter1, *iter2))
                {
                    this->adjacencies[&(*iter1)].push_back(&(*iter2));
                }
            }
        }
    }

    const string * get_ptr(const string &a) const
    {
        return &(*this->word_list.find(a));
    }

    bool can_adjacent(const string &a, const string &b)
    {
        int count = 0;
        for (string::const_iterator ia = a.begin(), ib = b.begin();
             ia != a.end();
             ia = next(ia), ib = next(ib))
        {
            if ((*ia) != (*ib))
            {
                count++;
            }
        }
        return count == 1;
    }

    const vector<const string *> &get_adjacencies(const string *a) const
    {
        /*
        cout << "adjacencies of " << *a << ": ";
        for (int i = 0; i < this->adjacencies.at(a).size(); i++)
        {
            cout << *this->adjacencies.at(a)[i] << ' ';
        }
        cout << endl;
        */

        return this->adjacencies.at(a);
    }

    const unordered_set<string> &get_word_list() const
    {
        return word_list;
    }

  private:
    unordered_set<string> word_list;
    map<const string *, vector<const string *> > adjacencies;
};


class Dijkstra {
  public:
    Dijkstra(const MyMap &map):
        m_map(map)
    {
        const unordered_set<string> &word_list(this->m_map.get_word_list());
        distance.clear();

        for(unordered_set<string>::const_iterator it = word_list.begin();
            it != word_list.end();
            it = next(it))
        {
            distance[&(*it)] = 0x7fffffff;
        }
    }
  public:
    class my_less {
      public:
        bool operator() (const MyPath &lhv, const MyPath &rhv) const {
            return distance[lhv.back()] > distance[rhv.back()];
        }
    };

    shared_ptr<vector<MyPath> > shortest_paths(
        const string &beginWord, const string &endWord)
    {
        shared_ptr<vector<MyPath> > result(new vector<MyPath>);
        priority_queue<MyPath, vector<MyPath>, my_less> paths;
        paths.push(MyPath(m_map.get_ptr(beginWord)));
        distance[m_map.get_ptr(beginWord)] = 0;
        int shortest_length = 0x7fffffff;
        while(!paths.empty())
        {
            MyPath current_path(paths.top());
            vector<const string *> adjacencies = this->m_map.get_adjacencies(current_path.back());
            for (vector<const string *>::const_iterator it = adjacencies.begin();
                 it != adjacencies.end();
                 it = next(it))
            {
                if (distance[*it] >= distance[current_path.back()] + 1)
                {
                    distance[*it] = distance[current_path.back()] + 1;
                    MyPath tmp(current_path);
                    tmp.push_back(*it);

                    if (**it != endWord)
                    {
                        if (tmp.size() < shortest_length)
                        {
                            paths.push(tmp);
                        }
                    }
                    else if (result->empty())
                    {
                        result->push_back(tmp);
                        shortest_length = tmp.size();
                    }
                    else if (tmp.size() < result->at(0).size())
                    {
                        result->clear();
                        result->push_back(tmp);
                        shortest_length = tmp.size();
                    }
                    else if (tmp.size() == result->at(0).size())
                    {
                        result->push_back(tmp);
                    }
                }
            }
            paths.pop();
        }

        return result;
    }
  private:
    const MyMap &m_map;
    static map<const string *, int> distance;
};

#ifndef __TEST__
map<const string *, int> Dijkstra::distance;
#endif

class Solution {
  public:
    vector<vector<string> > findLadders(
        string beginWord, string endWord, unordered_set<string> &wordList)
    {
        MyMap my_map(beginWord, endWord, wordList);
        shared_ptr<vector<MyPath> > tmp_result;

        Dijkstra algorithm(my_map);
        tmp_result = algorithm.shortest_paths(beginWord, endWord);

        vector<vector<string> > result;

        for (int i = 0; i < tmp_result->size(); i++)
        {
            tmp_result->at(i).print();
            result.push_back(tmp_result->at(i).get_vector());
        }

        return result;
    }
};

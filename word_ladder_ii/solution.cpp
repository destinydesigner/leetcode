#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <map>
#include <memory>
#include <iterator>
#include <algorithm>
#include <queue>


using namespace std;


class MyPath {
  public:
    MyPath(const string *a)
    {
        m_path.push_back(a);
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

    const string * back()
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

    bool exists(const string *a)
    {
        for(int i = 0; i < m_path.size(); i++)
        {
            if (m_path[i] == a)
            {
                return true;
            }
        }
        return false;
    }

    void print()
    {
        for(int i = 0; i < m_path.size(); i++)
        {
            cout << *(m_path[i]) << ' ';
        }
        cout << endl;
    }

  private:
    vector<const string *>  m_path;
};


class MyMap {
  public:
    MyMap(const string &beginWord, const string &endWord, const unordered_set<string> &wordList)
    {
        for (unordered_set<string>::const_iterator it = wordList.begin();
             it != wordList.end();
             it = next(it))
        {
            this->word_list.insert(*it);
        }
        this->word_list.insert(beginWord);
        this->word_list.insert(endWord);

        for (unordered_set<string>::const_iterator iter1 = this->word_list.begin();
             iter1 != wordList.end();
             iter1 = next(iter1))
        {
            for (unordered_set<string>::const_iterator iter2 = this->word_list.begin();
                 iter2 != wordList.end();
                 iter2 = next(iter2))
            {
                if (this->can_connect(*iter1, *iter2))
                {
                    this->adjacencies[&(*iter1)].push_back(&(*iter2));
                }
            }
        }
    }

  public:
    shared_ptr<vector<MyPath> > breadth_first_search(
        const string &beginWord, const string &endWord)
    {
        shared_ptr<vector<MyPath> > result(new vector<MyPath>);

        queue<shared_ptr<MyPath> > path_queue;
        queue<shared_ptr<MyPath> > back_path_queue;

        path_queue.push(shared_ptr<MyPath>(new MyPath(this->get_ptr(beginWord))));
        path_queue.push(shared_ptr<MyPath>(new MyPath(this->get_ptr(endWord))));

        int shortest_path_lenght = 0x7fffffff;

        while(path_queue.size())
        {
            shared_ptr<MyPath> current_path = path_queue.front();
            if (current_path->size() >= shortest_path_lenght)
            {
                path_queue.pop();
                continue;
            }

            const string *current_word(current_path->back());
            vector<const string *> adjacencies = this->get_adjacencies(current_word);
            for (vector<const string *>::const_iterator iter = adjacencies.begin();
                 iter != adjacencies.end();
                 iter = next(iter))
            {
                if (current_path->exists(*iter))
                {
                    continue;
                }
                shared_ptr<MyPath> new_path(
                    new MyPath(*current_path));
                new_path->push_back(*iter);
                path_queue.push(new_path);

                if (*iter == this->get_ptr(endWord))
                {
                    shortest_path_lenght = new_path->size();
                    result->push_back(*new_path);
                }
            }
            path_queue.pop();
        }
        return result;
    }

  private:
    void update_path_queue(queue<shared_ptr<MyPath> > &path_queue)
    {
    }

    const string * get_ptr(const string &a)
    {
        return &(*this->word_list.find(a));
    }

    bool can_connect(const string &a, const string &b)
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

    vector<const string *> get_adjacencies(const string *a)
    {
        return this->adjacencies[a];
    }

  private:
    unordered_set<string> word_list;
    map<const string *, vector<const string *> > adjacencies;
};


class Solution {
  public:
    vector<vector<string> > findLadders(
        string beginWord, string endWord, unordered_set<string> &wordList)
    {
        MyMap my_map(beginWord, endWord, wordList);
        shared_ptr<vector<MyPath> > tmp_result;

        tmp_result = my_map.breadth_first_search(beginWord, endWord);

        vector<vector<string> > result;

        for (int i = 0; i < tmp_result->size(); i++)
        {
            result.push_back(tmp_result->at(i).get_vector());
        }

        return result;
    }
};

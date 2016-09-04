#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <map>
#include <memory>
#include <iterator>
#include <algorithm>


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
        return;
        for(int i = 0; i < m_path.size(); i++)
        {
            cout << *(m_path[i]) << ' ';
        }
        cout << endl;
    }

    void pop_back()
    {
        m_path.pop_back();
    }

    void reverse()
    {
        ::reverse(m_path.begin(), m_path.end());
    }

    vector<const string *>::const_iterator begin() const
    {
        return m_path.begin();
    }

    vector<const string *>::const_iterator end() const
    {
        return m_path.end();
    }

    void extend(const MyPath &a)
    {
        for(vector<const string *>::const_iterator it = a.begin();
            it != a.end();
            it = next(it))
        {
            m_path.push_back(*it);
        }
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
                if (this->can_adjacent(*iter1, *iter2))
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
        shared_ptr<vector<MyPath> > result(NULL);

        vector<shared_ptr<MyPath> > path_deque;
        vector<shared_ptr<MyPath> > back_path_deque;

        path_deque.push_back(shared_ptr<MyPath>(new MyPath(this->get_ptr(beginWord))));
        back_path_deque.push_back(shared_ptr<MyPath>(new MyPath(this->get_ptr(endWord))));

        while(true)
        {
            if (path_deque.empty() && back_path_deque.empty())
            {
                return result;
            }
            result = this->try_to_find_path(path_deque, back_path_deque);
            if (result->size())
            {
                return result;
            }
            this->update_path_deque(path_deque);
            result = this->try_to_find_path(path_deque, back_path_deque);
            if (result->size())
            {
                return result;
            }
            this->update_path_deque(back_path_deque);
        }
        return result;
    }

  private:
    void update_path_deque(vector<shared_ptr<MyPath> > &path_deque)
    {
        vector<shared_ptr<MyPath> > tmp_q(path_deque);
        path_deque.clear();

        for (vector<shared_ptr<MyPath> >::iterator q_it = tmp_q.begin();
             q_it != tmp_q.end();
             q_it = next(q_it))
        {
            shared_ptr<MyPath> current_path = *q_it;

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
                path_deque.push_back(new_path);
                new_path->print();
            }
        }
    }

    shared_ptr<vector<MyPath> > try_to_find_path(
        vector<shared_ptr<MyPath> > &a, vector<shared_ptr<MyPath> > &b)
    {
        // cout << "try to find path" << endl;
        shared_ptr<vector<MyPath> > result(new vector<MyPath>);

        for (vector<shared_ptr<MyPath> >::iterator iter1 = a.begin();
             iter1 != a.end();
             iter1 = next(iter1))
        {
            (*iter1)->print();
            for (vector<shared_ptr<MyPath> >::iterator iter2 = b.begin();
                 iter2 != b.end();
                 iter2 = next(iter2))
            {
                (*iter2)->print();
                if ((*iter1)->back() == (*iter2)->back())
                {
                    result->push_back(**iter1);
                    MyPath tmp(**iter2);
                    tmp.pop_back();
                    tmp.reverse();
                    result->back().extend(tmp);
                }
            }
        }

        return result;
    }


    const string * get_ptr(const string &a)
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

    vector<const string *> get_adjacencies(const string *a)
    {
        /*
        cout << "adjacencies of " << *a << ": ";
        for (int i = 0; i < this->adjacencies[a].size(); i++)
        {
            cout << *this->adjacencies[a][i] << ' ';
        }
        cout << endl;
        */
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

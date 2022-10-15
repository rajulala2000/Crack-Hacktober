class Trie
{
    public:
    struct Node
    {
        private:
            Node *child[27];
            int endIdx;

        public:
            bool contains(char &ch)
            {
                return (child[ch - 'a'] != NULL);
            }

            void putNode(char &ch, Node *newNode)
            {
                child[ch - 'a'] = newNode;
            }

            Node *getNext(char &ch)
            {
                return child[ch - 'a'];
            }

            void setIdx(int &i)
            {
                endIdx = i;
            }

            int getIdx()
            {
                return endIdx;
            }
    };

    Node *root;

    public:
    Trie()
    {
        root = new Node();
    }

    void insert(string &word, int &idx)
    {
        Node *temp = root;

        for(auto &ch : word)
        {
            if(!temp -> contains(ch))
            {
                temp -> putNode(ch, new Node());
            }

            temp = temp -> getNext(ch);
            temp -> setIdx(idx);
        }

    }

    int startsWith(string &word)
    {
        Node *temp = root;

        for(auto &ch : word)
        {
            if(!temp -> contains(ch))
            {
                return -1;
            }

            temp = temp -> getNext(ch);
        }

        return temp -> getIdx();
    }
};

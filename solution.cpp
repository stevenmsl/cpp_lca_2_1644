#include "solution.h"

#include <functional>

using namespace sol1644;
using namespace std;

/*takeways
  - traverse the tree only once
  - use DFS to make sure that the order
    of visiting the nodes will yield
    lca if it does exist
  - track if we have visited both p and
    q
  - visiting tree
    - return a node only if one of the following
      is true
      - the node is either p or q
      - p and q reside in a different subtree
        of this node - lca found!
    - or just return whichever subtree is not
      a nullptr. Return a nullptr if both
      subtrees a nullptr
*/

Node *Solution::lca(Node *tree, int p, int q)
{
    /*
      - use to track if both p an q are
        in the tree
      - expect this to be 2 - p and q
    */
    int found = 0;

    function<Node *(Node *, int, int)> visit = [&found, &visit](Node *node, int p, int q)
    {
        if (node == nullptr)
            return node;
        /*
          - we are doing a DFS so lca is guarranted
            as we are working up from the bottom
            of the tree
          - you might be thinking why we don't
            check if the node is p or q first
            before visiting its left and right?
            - we will not be able to mark q
              as visited if q is in p's
              subtree for example as we
              will return already once we
              found p
        */
        auto left = visit(node->left, p, q);
        auto right = visit(node->right, p, q);

        /*
          - if this node is p or q, we can ignore
            its children and just return
          - why? ley say it's p
            - if q is in p's subtree, the lca
              will be p
            - if q is not in p's subtree, the
              lca must be p's ancestor if
              it does exist
            - either way, we will do the same
              thing: just report back that we
              found p!
        */
        if (node->val == p || node->val == q)
        {
            found++;
            return node;
        }

        /* this is the tricky part
           - draw a tree to help we understand
                 5
                /  \
               6   2
                 /  \
                7    4
           - let say p=5, q=1
           - the leave node 6 will report back its
             right child which is a nullptr; so we
             are good here with leave node
           - node 7 and 4 will report back a nullptr
             for the same reason.
           - for node 2 it will just report back
             what the right child tell it since
             it's left child is a nullptr. Node 2
             will report back what Node 4 tells it
             : nullptr
           - so p or q is not in 2's subtrees
           - node 5 won't even come here for
             the reason mentioned above
        */

        /* well not in the left; maybe in the right? */
        if (left == nullptr)
            /*
              - if it's not in the right either we would return
                a nullptr anway
            */
            return right;
        else if (right == nullptr)
            /* well left for sure is not a nullptr */
            return left;
        else
            /*
              - only when we can find p and q, and each of them
                resides in a different subtree of this node
                we can then declare this is the lca
              - node's ancestor will be just passing along that
                message
              - take this node's parent as an example:
                - this node will be either in the left or right child
                  of its parent
                - this node's sibling must report back a nullptr as we
                  already found p and q here!
                - so the parent just rely the message to
                  this node's grandparents that the node is
                  the lca
            */
            return node;
    };

    auto ancestor = visit(tree, p, q);
    if (found != 2)
        return nullptr;

    return ancestor;
}
#pragma once

namespace containers {

	template <typename K>
	struct node;
	template <typename K>
	class bst;

	enum side { ORPHAN, LEFT, RIGHT, MISSATTACHED };    // describe relation of node with it's parrent
	enum order { INORDER, PREORDER, POSTORDER };        // describes tree traversal order

}
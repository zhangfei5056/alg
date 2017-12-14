#coding:utf-8
class TreeNode:
    def __init__(self, val):
        self.val = val
        self.left, self.right = None, None

''' 1 get binary tree height using recursive method'''
def height(root):
    if not root:
        return 0
    else:
        left_height = height(root.left)
        right_heigh = height(root.right)
        return max(left_height, right_heigh) + 1

'''2 get binary tree height convert recursive method to stack simulate'''
def nonRecursiveHeight(root):
    height_res = 0
    if not root:
        return height_res
    stack = [(root, 1)]
    while stack:
        node, h = stack.pop()
        height_res = max(height_res, h)
        stack.append( (node.left, h+1) ) if node.left else 0
        stack.append( (node.right, h+1) ) if node.right else 0
    return height_res


'''3 get diameter from binary tree using recursive method'''
def diameterBinaryTree(root):
    if not root:
        return 0
    else:
        left_height = height(root.left)
        right_heigh = height(root.right)
        twoSide = left_height + right_heigh
        maxLeft = diameterBinaryTree(root.left)
        maxRight = diameterBinaryTree(root.right)
        return max(maxLeft, maxRight, twoSide)



'''4 get diameter from binary convert recursive method to stack.......I dont konw how to do that.'''
def diameterBinaryTree_nonRecursive(root):
    if not root:
        return 0
    # lh = height(root.left)
    # rh = height(root.right)
    # twoSide = lh + rh
    # stack = [(root, twoSide)]
    # while stack:
    #     node, node_twoSide = stack.pop()
        

if __name__ == '__main__':
    a1 = TreeNode(1)
    a2 = TreeNode(2)
    a3 = TreeNode(3)
    a4 = TreeNode(4)
    a5 = TreeNode(5)
    a6 = TreeNode(6)
    a7 = TreeNode(7)
    a1.left = a2
    a1.right = a3
    a2.left = a4
    a2.right = a5
    a3.right = a6
    a5.left = a7


    root = a1
    print height(root)
    print nonRecursiveHeight(root)
    print diameterBinaryTree(root)


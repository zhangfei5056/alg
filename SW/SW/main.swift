import Foundation

Tree.testTree()
LinkedList.testLinkedList()
Graph.testGraph()


//let a:[Any]? = [1,2,3,"#", 4]
let a:[Any]? = []
func tt(_ a:[Any]?) {
    guard let a = a, a.count != 0 else {print("not");return}
    for i in a {
        print(i)
    }
}


tt(a)

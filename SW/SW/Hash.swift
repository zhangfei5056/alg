import Foundation



class Hash:Hashable {
    
    static private func address(any:AnyObject) -> Int {
        let bits = Unmanaged<AnyObject>.passUnretained(any as AnyObject)
        let ptr = bits.toOpaque()
        return ptr.hashValue
    }
    
    static public func hash(any:AnyObject) -> Int {
        return address(any: any)
    }
    
    var hashValue: Int {
        return Hash.hash(any: self)
    }
    
    static func ==(lhs: Hash, rhs: Hash) -> Bool {
        return lhs.hashValue == rhs.hashValue
    }
}

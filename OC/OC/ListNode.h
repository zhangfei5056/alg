#import <Foundation/Foundation.h>

@interface ListNode : NSObject

@property (nonatomic, strong) id val;
@property (nonatomic, strong) ListNode *next;

+ (void)demo;
- (instancetype)initWith:(id)val;
+ (ListNode *)toLinkedList:(NSArray *)dataList;
+ (ListNode *)toLinkedListFromStr:(NSString *)str;
+ (NSArray *)toList:(ListNode *)head;

@end

@implementation ListNode

- (instancetype)initWith:(id)val {
    self = [super init];
    if (self) {
        _val = val;
        _next = nil;
    }
    return self;
}

- (NSUInteger)hash {
    return [NSString stringWithFormat:@"%p", self].hash;
}


- (BOOL)isEqual:(TreeNode *)object {
    if (![object isKindOfClass:self.class]) {
        return NO;
    }
    return object.hash == self.hash;
}

- (id)copyWithZone:(NSZone *)zone {
    ListNode *objectCopy = [[ListNode allocWithZone:zone] init];
    objectCopy.val = self.val;
    objectCopy.next = self.next;
    return objectCopy;
}

- (NSString *)description {
    return [NSString stringWithFormat:@"%@", self.val];
}

+ (void)demo {
    NSArray *a = @[@1, @2, @3, @4, @5];
    ListNode *head = [self toLinkedList:a];
    NSArray *res = [self toList:head];
    NSLog(@"🌞👉🏻%@👈🏻🌞", res);
    
    ListNode *node = [self toLinkedListFromStr:@"-1->3->3->2->2->null"];
    NSArray *res2 = [self toList:node];
    NSLog(@"🌞👉🏻%@👈🏻🌞",res2);
}


+ (NSArray *)formatStrToList:(NSString *)str {
    NSMutableArray *ary = [str componentsSeparatedByString:@"->"].mutableCopy;
    if (ary.count > 0) {
        [ary removeLastObject];
    }
    return [NSArray arrayWithArray:ary];
}

+ (ListNode *)toLinkedList:(NSArray *)dataList {
    if (!dataList || dataList.count == 0) return nil;
    ListNode *dummy = [[ListNode alloc] initWith:0];
    ListNode *pDummy = dummy;
    int i = 0;
    while (i < dataList.count) {
        ListNode *node = [[ListNode alloc] initWith:dataList[i]];
        pDummy.next = node;
        pDummy = pDummy.next;
        i ++;
    }
    return dummy.next;
}

+ (ListNode *)toLinkedListFromStr:(NSString *)str {
    NSArray *ary = [self formatStrToList:str];
    return [self toLinkedList:ary];
}

+ (NSArray *)toList:(ListNode *)head {
    if (!head) return @[];
    
    NSMutableArray *res = @[].mutableCopy;
    while (head) {
        [res addObject:head.val];
        head = head.next;
    }
    return [NSArray arrayWithArray:res];
}

@end

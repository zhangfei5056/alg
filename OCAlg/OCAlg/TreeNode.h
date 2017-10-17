#import <Foundation/Foundation.h>

@interface TreeNode : NSObject

@property (nonatomic, assign) int val;
@property (nonatomic, strong) TreeNode *left;
@property (nonatomic, strong) TreeNode *right;

+ (void)demo;
- (instancetype)initWith:(int)val;
+ (TreeNode *)toTree:(NSMutableArray *)ary;
+ (NSArray *)toList:(TreeNode *)root;
@end

@implementation TreeNode

- (instancetype)initWith:(int)val {
    self = [super init];
    if (self) {
        _val = val;
        _left = nil;
        _right = nil;
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
    TreeNode *objectCopy = [[TreeNode allocWithZone:zone] init];
    objectCopy.val = self.val;
    objectCopy.left = self.left;
    objectCopy.right = self.right;
    return objectCopy;
}

+ (TreeNode *)toTree:(NSMutableArray *)ary {
    if (!ary || [ary count] == 0) {
        return nil;
    }
    if ([ary count] % 2 == 0) {
        [ary addObject:@"#"];
    }
    TreeNode *root = [[TreeNode alloc] initWith:[ary[0] intValue]];
    int index = 1;
    NSMutableArray *queue = [@[root] mutableCopy];
    while (index < [ary count]) {
        TreeNode *parent = [queue objectAtIndex:0];
        [queue removeObjectAtIndex:0];
        if (![ary[index] isKindOfClass:[NSString class]]) {
            TreeNode *node = [[TreeNode alloc] initWith:[ary[index] intValue]];
            parent.left = node;
            [queue addObject:node];
        }
        index ++;
        if (![ary[index] isKindOfClass:[NSString class]]) {
            TreeNode *node = [[TreeNode alloc] initWith:[ary[index] intValue]];
            parent.right = node;
            [queue addObject:node];
        }
        index ++;
    }
    return root;
}

+ (NSArray *)toList:(TreeNode *)root {
    if (!root) {
        return @[];
    }
    NSMutableArray *res = [NSMutableArray array];
    NSMutableArray *queue = [@[root] mutableCopy];
    while ([queue count] != 0) {
        TreeNode *node = queue[0];
        [queue removeObjectAtIndex:0];
        if (!node || (NSNull *)node == [NSNull null]) {
            [res addObject:@"#"];
        }else {
            [res addObject:@(node.val)];
            [queue addObject:node.left? node.left: [NSNull null]];
            [queue addObject:node.right? node.right: [NSNull null]];
        }
    }
    while ([[res lastObject] isKindOfClass:[NSString class]] && [[res lastObject] isEqualToString:@"#"]) {
        [res removeLastObject];
    }
    return [NSArray arrayWithArray:res];
}

+ (void)demo {
    NSMutableArray *ary = [@[@1, @2, @3, @4, @5, @6, @7, @"#", @8, @"#", @"#", @"#", @"#", @9] mutableCopy];
    TreeNode *root = [TreeNode toTree:ary];
    NSArray *list = [TreeNode toList:root];
    NSLog(@"🌞👉%@👈🌞",[NSString stringWithFormat:@"%@", list]);
}
@end

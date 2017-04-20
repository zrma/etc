//
//  main.swift
//  Test
//
//  Created by zrma on 2016. 10. 13..
//  Copyright © 2016년 zrma. All rights reserved.
//

import Foundation

var total = 0

for i in 1...10000000
{
    if(i % 2 == 0)
    {
        total += 1
    }
}

print("total : \(total)")

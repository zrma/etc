//
//  GameScene.swift
//  SwiftJump
//
//  Created by zrma on 2016. 12. 7..
//  Copyright © 2016년 zrma. All rights reserved.
//

import SpriteKit
import CoreMotion

class GameScene: SKScene {
    
    var motionManager : CMMotionManager!
    
    override func didMove(to view: SKView) {
        motionManager = CMMotionManager()
        motionManager.accelerometerUpdateInterval = 0.1
        
        motionManager.startAccelerometerUpdates(to: OperationQueue.current!, withHandler: {
            (data:CMAccelerometerData?, error:Error?) in
            
            print("x:\(data?.acceleration.x)  y:\(data?.acceleration.y)  z:\(data?.acceleration.z)")
        } )
    }
    
    
    func touchDown(atPoint pos : CGPoint) {
    }
    
    func touchMoved(toPoint pos : CGPoint) {
    }
    
    func touchUp(atPoint pos : CGPoint) {
    }
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        for t in touches { self.touchDown(atPoint: t.location(in: self)) }
    }
    
    override func touchesMoved(_ touches: Set<UITouch>, with event: UIEvent?) {
        for t in touches { self.touchMoved(toPoint: t.location(in: self)) }
    }
    
    override func touchesEnded(_ touches: Set<UITouch>, with event: UIEvent?) {
        for t in touches { self.touchUp(atPoint: t.location(in: self)) }
    }
    
    override func touchesCancelled(_ touches: Set<UITouch>, with event: UIEvent?) {
        for t in touches { self.touchUp(atPoint: t.location(in: self)) }
    }
    
    
    override func update(_ currentTime: TimeInterval) {
        // Called before each frame is rendered
    }
}

//
//  GameScene.swift
//  SwiftPinball
//
//  Created by zrma on 2016. 3. 25..
//  Copyright (c) 2016년 zrma. All rights reserved.
//

import SpriteKit

class GameScene: SKScene, SKPhysicsContactDelegate {
    
    var gameoverFlag = false
    var count: NSInteger = 0
    
    let gameoverLabel = SKLabelNode(fontNamed: "Hiragino Kaku Gothic ProN")
    let pointLabel = SKLabelNode(fontNamed: "Hiragino Kaku Gothic PorN")
    
    var ball = SKSpriteNode(imageNamed: "ball")
    var armRight = SKSpriteNode(imageNamed: "rightarm")
    var armLeft = SKSpriteNode(imageNamed: "leftarm")
    var back = SKSpriteNode(imageNamed: "back")
    var wallLeft = SKSpriteNode(imageNamed: "wallleft")
    var wallRight = SKSpriteNode(imageNamed: "wallright")
    var triangleLeft = SKSpriteNode(imageNamed: "triangleleft")
    var triangleRight = SKSpriteNode(imageNamed: "triangleright")
    var monster1 = SKSpriteNode(imageNamed: "monster1a")
    var monster2 = SKSpriteNode(imageNamed: "monster2a")
    var monster3 = SKSpriteNode(imageNamed: "monster3a")
    let playSound = SKAction.playSoundFileNamed("click.mp3", waitForCompletion: false)
    
    func makeBall() {
        
        _ = SKSpriteNode(imageNamed: "ball")
        
        ball.physicsBody = SKPhysicsBody(circleOfRadius: 15)
        ball.physicsBody?.contactTestBitMask = 1
        
        ball.position = CGPoint(x: 165, y: 500)
        self.addChild(ball)
    }
    
    func didBegin(_ contact: SKPhysicsContact) {
        if let nodeA = contact.bodyA.node {
            if let nodeB = contact.bodyB.node {
                if  nodeA.name == "monster1" || nodeB.name == "monster1" ||
                    nodeA.name == "monster2" || nodeB.name == "monster2" ||
                    nodeA.name == "monster3" || nodeB.name == "monster3" {
                    
                    ball.run(playSound)
                    
                    let particle = SKEmitterNode(fileNamed: "StarParticle")
                    self.addChild(particle!)
                    
                    let removeAction = SKAction.removeFromParent()
                    let durationAction = SKAction.wait(forDuration: 1)
                    let sequenceAction = SKAction.sequence([durationAction, removeAction])
                    particle?.run(sequenceAction)
                    
                    particle?.position = CGPoint(x: ball.position.x, y: ball.position.y)
                    particle?.alpha = 1
                    
                    let fadeAction = SKAction.fadeAlpha(to: 0, duration: 0.5)
                    particle?.run(fadeAction)
                    
                    count += 10
                    let pointString: String = "\(count)点"
                    pointLabel.text = pointString
                }
            }
        }
    }
    
    func gameover() {
        gameoverLabel.text = "ゲームオーバー"
        gameoverLabel.fontSize = 30
        gameoverLabel.fontColor = UIColor(red: 0, green: 0, blue: 0, alpha: 1)
        gameoverLabel.position = CGPoint(x: self.frame.midX, y: self.frame.midY)
        self.addChild(gameoverLabel)
        
        gameoverFlag = true
    }
    
    func reset() {
        gameoverFlag = false
        gameoverLabel.removeFromParent()
        
        ball.removeFromParent()
        self.makeBall()
        
        count = 0
    }
    
    override func didMove(to view: SKView) {
        
        back.position = CGPoint(x: 0, y: 0)
        back.anchorPoint = CGPoint(x: 0, y: 0)
        self.addChild(back)
        self.size = CGSize(width: 320, height: 568)
        
        self.physicsWorld.gravity = CGVector(dx: 0, dy: -3.0)
        self.physicsWorld.contactDelegate = self
        
        makeBall()
        
        wallLeft.physicsBody = SKPhysicsBody(texture: SKTexture(imageNamed: "wallleft"), size: wallLeft.size)
        wallLeft.physicsBody?.restitution = 0.1
        wallLeft.physicsBody?.isDynamic = false
        wallLeft.physicsBody?.contactTestBitMask = 1
        wallLeft.position = CGPoint(x: 80, y: 284)
        self.addChild(wallLeft)
        
        wallRight.physicsBody = SKPhysicsBody(texture: SKTexture(imageNamed: "wallright"), size: wallRight.size)
        wallRight.physicsBody?.restitution = 0.1
        wallRight.physicsBody?.isDynamic = false
        wallRight.physicsBody?.contactTestBitMask = 1
        wallRight.position = CGPoint(x: 240, y: 284)
        self.addChild(wallRight)
        
        armRight.physicsBody = SKPhysicsBody(texture: SKTexture(imageNamed: "rightarm"), size: armRight.size)
        armRight.physicsBody?.restitution = 1.2
        armRight.physicsBody?.isDynamic = false
        armRight.physicsBody?.contactTestBitMask = 1
        armRight.position = CGPoint(x: 220, y: 70)
        self.addChild(armRight)
        
        armLeft.physicsBody = SKPhysicsBody(texture: SKTexture(imageNamed: "leftarm"), size: armLeft.size)
        armLeft.physicsBody?.restitution = 1.5
        armLeft.physicsBody?.isDynamic = false
        armLeft.physicsBody?.contactTestBitMask = 1
        armLeft.position = CGPoint(x: 100, y: 70)
        self.addChild(armLeft)
        
        monster1.name = "monster1"
        monster1.physicsBody = SKPhysicsBody(texture: SKTexture(imageNamed: "monster1a"), size: monster1.size)
        monster1.physicsBody?.restitution = 1.3
        monster1.physicsBody?.isDynamic = false
        monster1.physicsBody?.contactTestBitMask = 1
        monster1.position = CGPoint(x: 140, y: 410)
        self.addChild(monster1)
        
        let scaleA = SKAction.scale(to: 0.5, duration: 0.5)
        let scaleB = SKAction.scale(to: 1.0, duration: 1.5)
        let scaleSequence = SKAction.sequence([scaleA, scaleB])
        let scalerepeatAction = SKAction.repeatForever(scaleSequence)
        monster1.run(scalerepeatAction)
        
        let paraparaAction1 = SKAction.animate(with: [SKTexture(imageNamed: "monster1a.png"), SKTexture(imageNamed: "monster1b.png")], timePerFrame: 0.5)
        let paraparaRepeatAction1 = SKAction.repeatForever(paraparaAction1)
        monster1.run(paraparaRepeatAction1)
        
        monster2.name = "monster2"
        monster2.physicsBody = SKPhysicsBody(texture: SKTexture(imageNamed: "monster2a"), size: monster2.size)
        monster2.physicsBody?.restitution = 1.3
        monster2.physicsBody?.isDynamic = false
        monster2.physicsBody?.contactTestBitMask = 1
        monster2.position = CGPoint(x: 100, y: 300)
        self.addChild(monster2)
        
        let moveA = SKAction.move(to: CGPoint(x: 100, y: 300), duration: 1)
        let moveB = SKAction.move(to: CGPoint(x: 200, y: 300), duration: 1)
        let moveSequence = SKAction.sequence([moveA, moveB])
        let moverepeatAction = SKAction.repeatForever(moveSequence)
        monster2.run(moverepeatAction)
        
        let paraparaAction2 = SKAction.animate(with: [SKTexture(imageNamed: "monster2a.png"), SKTexture(imageNamed: "monster2b.png")], timePerFrame: 0.5)
        let paraparaRepeatAction2 = SKAction.repeatForever(paraparaAction2)
        monster2.run(paraparaRepeatAction2)
        
        monster3.name = "monster3"
        monster3.physicsBody = SKPhysicsBody(texture: SKTexture(imageNamed: "monster3a"), size: monster3.size)
        monster3.physicsBody?.restitution = 1.3
        monster3.physicsBody?.isDynamic = false
        monster3.physicsBody?.contactTestBitMask = 1
        monster3.position = CGPoint(x: 150, y: 200)
        self.addChild(monster3)
        
        let rotateAction = SKAction.rotate(byAngle: CGFloat(360 * M_PI / 180), duration: 3)
        let rotateRepeatAction = SKAction.repeatForever(rotateAction)
        SKAction.repeat(rotateRepeatAction, count: 1000)
        monster3.run(rotateRepeatAction)
        
        let paraparaAction3 = SKAction.animate(with: [SKTexture(imageNamed: "monster3a.png"), SKTexture(imageNamed: "monster3b.png")], timePerFrame: 0.5)
        let paraparaRepeatAction3 = SKAction.repeatForever(paraparaAction3)
        monster3.run(paraparaRepeatAction3)
        
        triangleLeft.name = "leftTriangle"
        triangleLeft.physicsBody = SKPhysicsBody(texture: SKTexture(imageNamed: "triangleleft"), size: triangleLeft.size)
        triangleLeft.physicsBody?.restitution = 0.5
        triangleLeft.physicsBody?.isDynamic = false
        triangleLeft.position = CGPoint(x: 80, y: 150)
        self.addChild(triangleLeft)
        
        triangleRight.name = "rightTriangle"
        triangleRight.physicsBody = SKPhysicsBody(texture: SKTexture(imageNamed: "triangleright"), size: triangleRight.size)
        triangleRight.physicsBody?.restitution = 0.5
        triangleRight.physicsBody?.isDynamic = false
        triangleRight.position = CGPoint(x: 240, y: 150)
        self.addChild(triangleRight)
        
        pointLabel.text = "0点"
        pointLabel.fontSize = 25
        pointLabel.fontColor = UIColor(red: 1, green: 1, blue: 1, alpha: 1)
        pointLabel.position = CGPoint(x: self.frame.midX, y: self.frame.midY)
        self.addChild(pointLabel)
        pointLabel.position = CGPoint(x: 160, y: 497)
    }
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
       /* Called when a touch begins */
        
        for touch in touches {
            _ = touch.location(in: self)
            
            let swingAction1 = SKAction.rotate(byAngle: CGFloat(-M_PI * 0.25), duration: 0.05)
            let swingAction2 = SKAction.rotate(byAngle: CGFloat(M_PI * 0.25), duration: 0.05)
            armRight.run(swingAction1)
            armLeft.run(swingAction2)
        }
        
        if gameoverFlag == true {
            self.reset()
        }
    }
    
    override func touchesEnded(_ touches: Set<UITouch>, with event: UIEvent?) {
        for touch in touches {
            _ = touch.location(in: self)
            
            let swingAction1 = SKAction.rotate(byAngle: CGFloat(-M_PI * 0.25), duration: 0.05)
            let swingAction2 = SKAction.rotate(byAngle: CGFloat(M_PI * 0.25), duration: 0.05)
            armRight.run(swingAction2)
            armLeft.run(swingAction1)
        }
    }
   
    override func update(_ currentTime: TimeInterval) {
        /* Called before each frame is rendered */
        
        if gameoverFlag == false {
            if ball.position.y < 0 {
                self.gameover();
            }
        }
    }
}

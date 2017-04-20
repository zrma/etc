//
//  GameScene.swift
//  HelpNagoyaSpecialty
//
//  Created by zrma on 2016. 2. 11..
//  Copyright © 2016년 zrma. All rights reserved.
//

import Foundation
import SpriteKit

class GameScene : SKScene, SKPhysicsContactDelegate {
    ////////////////////////////////////////////////////////////////////////////////
    // 프로퍼티
    ////////////////////////////////////////////////////////////////////////////////
    
    // 그릇
    var bowl:SKSpriteNode?
    
    // 타이머
    var timer:Timer?
    
    // 추락 판정용 쉐이프 노드
    var lowestShape:SKShapeNode?
    
    // 점수
    var score = 0
    var scoreLabel:SKLabelNode?
    var scoreList = [100, 200, 300, 500, 800, 1000, 1500]
    
    override func didMove(to view: SKView) {
        self.initGame()
        self.startGame()
    }
    
    func initGame() {
        self.initGravity()
        self.initBackground()
        self.initLowestGround()
        self.initBowl()
        self.initScoreLabel()
    }
    
    func initGravity() {
        self.physicsWorld.gravity = CGVector(dx: 0.0, dy: -2.0)
        self.physicsWorld.contactDelegate = self
    }
    
    func initBackground() {
        let background = SKSpriteNode(imageNamed: "background")
        
        background.position = CGPoint(x: self.size.width * 0.5, y: self.size.height * 0.5)
        background.size = self.size
        addChild(background)
    }
    
    func initLowestGround() {
        // 낙하 판정용 쉐이프 노드 추가
        let lowestShape = SKShapeNode(rectOf: CGSize(width: self.size.width * 3, height: 10))
        lowestShape.position = CGPoint(x: self.size.width * 0.5, y: -10)
        
        // 낙하 판정용 쉐이프에 PhysicsBody 생성
        let physicsBody = SKPhysicsBody(rectangleOf: lowestShape.frame.size)
        physicsBody.isDynamic = false
        
        // 접촉 탐지용 비트마스크 (일종의 태그)
        physicsBody.contactTestBitMask = 0x1 << 1
        lowestShape.physicsBody = physicsBody
        
        self.addChild(lowestShape)
        self.lowestShape = lowestShape
    }
    
    func initBowl() {
        let bowlTexture = SKTexture(imageNamed: "bowl")
        let bowl = SKSpriteNode(texture: bowlTexture)
        
        bowl.position = CGPoint(x: self.size.width * 0.5, y: 100)
        bowl.size = CGSize(width: bowlTexture.size().width * 0.5, height: bowlTexture.size().height * 0.5)
        bowl.physicsBody = SKPhysicsBody(texture: bowlTexture, size: bowl.size)
        bowl.physicsBody?.isDynamic = false
        
        self.bowl = bowl
        self.addChild(bowl)
    }
    
    func initScoreLabel() {
        let scoreLabel = SKLabelNode(fontNamed: "Helvetica")
        scoreLabel.position = CGPoint(x: self.size.width * 0.92, y: self.size.height * 0.78)
        scoreLabel.text = "¥0"
        scoreLabel.fontSize = 32
        scoreLabel.horizontalAlignmentMode = SKLabelHorizontalAlignmentMode.right
        scoreLabel.fontColor = UIColor.green
        
        self.addChild(scoreLabel)
        self.scoreLabel = scoreLabel
    }
    
    func startGame() {
        self.fallNagoyaSpecialty()
        self.timer = Timer.scheduledTimer(timeInterval: 3, target: self, selector: #selector(GameScene.fallNagoyaSpecialty), userInfo: nil, repeats: true)
    }
    
    func fallNagoyaSpecialty() {
        // 0 ~ 6 랜덤
        let index = Int(arc4random_uniform(7))
        let texture = SKTexture(imageNamed: "\(index)")
        let sprite = SKSpriteNode(texture: texture)
        
        sprite.position = CGPoint(x: self.size.width * 0.5, y: self.size.height)
        sprite.size = CGSize(width: texture.size().width * 0.5, height: texture.size().height * 0.5)
        
        sprite.physicsBody = SKPhysicsBody(texture: texture, size: sprite.size)
        
        // 접촉 탐지용 비트마스크 (일종의 태그)
        sprite.physicsBody?.contactTestBitMask = 0x1 << 1
        
        self.addChild(sprite)
        
        self.score += self.scoreList[index]
        self.scoreLabel?.text = "¥\(self.score)"
    }
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        if let touch: AnyObject = touches.first {
            let location = touch.location(in: self)
            let action = SKAction.move(to: CGPoint(x: location.x, y: 100), duration: 0.2)
            self.bowl?.run(action)
        }
    }
    
    override func touchesMoved(_ touches: Set<UITouch>, with event: UIEvent?) {
        if let touch: AnyObject = touches.first {
            let location = touch.location(in: self)
            let action = SKAction.move(to: CGPoint(x: location.x, y: 100), duration: 0.2)
            self.bowl?.run(action)
        }
    }
    
    func didBegin(_ contact: SKPhysicsContact) {
        if contact.bodyA.node == self.lowestShape || contact.bodyB.node == self.lowestShape {
            let sprite = SKSpriteNode(imageNamed: "gameover")
            
            sprite.position = CGPoint(x: self.size.width * 0.5, y: self.size.height * 0.5)
            self.addChild(sprite)
            
            self.isPaused = true
            self.timer?.invalidate()
        }
    }
}

//
//  GameScene.swift
//  ShrimpSwim
//
//  Created by zrma on 2016. 2. 13..
//  Copyright (c) 2016년 zrma. All rights reserved.
//

import SpriteKit

class GameScene: SKScene, SKPhysicsContactDelegate
{
    // 태그용 마스크 비트
    struct ColliderType
    {
        static let Player: UInt32   = ( 1 << 0 )
        static let World: UInt32    = ( 1 << 1 )
        static let Coral: UInt32    = ( 1 << 2 )
        static let Score: UInt32    = ( 1 << 3 )
        static let None: UInt32     = ( 1 << 4 )
    }
    
    struct Constants
    {
        // 플레이어 캐릭터 스프라이트
        static let PlayerImages = ["shrimp01", "shrimp02", "shrimp03", "shrimp04"]
    }
    
    var baseNode: SKNode!
    var coralNode: SKNode!
    var player: SKSpriteNode!
    var scoreLabelNode: SKLabelNode!
    var score: UInt32!
    
    func setupBackgroundSea()
    {
        // 배경 이미지 로딩
        let texture = SKTexture(imageNamed: "background")
        texture.filteringMode = .nearest
        
        // 화면 대비 텍스쳐 사이즈 기반으로 횡 스크롤링에 필요한 이미지 수 계산
        let needNumber = 2.0 + (self.frame.size.width / texture.size().width)
        
        // 횡 스크롤 애니메이션 구성
        let moveAnimation = SKAction.moveBy(x: -texture.size().width, y: 0.0, duration: TimeInterval(texture.size().width / 10.0))
        let resetAnimation = SKAction.moveBy(x: texture.size().width, y: 0.0, duration: 0.0)
        let repeatForeverAnimation = SKAction.repeatForever(SKAction.sequence([moveAnimation, resetAnimation]))
        
        // 횡 스크롤 애니메이션 설정
        for i: CGFloat in stride(from: CGFloat(0), to: needNumber, by: 1.0)
        {
            let sprite = SKSpriteNode(texture: texture)
            sprite.zPosition = -100.0
            sprite.position = CGPoint(x: i * sprite.size.width, y: self.frame.size.height / 2.0)
            sprite.run(repeatForeverAnimation)
            baseNode.addChild(sprite)
        }
    }
    
    func setupBackgroundRock()
    {
        // 하단 바위 이미지
        let under = SKTexture(imageNamed: "rock_under")
        under.filteringMode = .nearest
        
        // 화면 대비 텍스쳐 사이즈 기반으로 횡 스크롤링에 필요한 이미지 수 계산
        var needNumber = 2.0 + (self.frame.size.width / under.size().width)
        
        // 횡 스크롤 애니메이션 구성
        let moveUnderAnimation = SKAction.moveBy(x: -under.size().width, y: 0.0, duration: TimeInterval(under.size().width / 20.0))
        let resetUnderAnimation = SKAction.moveBy(x: under.size().width, y: 0.0, duration: 0.0)
        let repeatForeverUnderAnimation = SKAction.repeatForever(SKAction.sequence([moveUnderAnimation, resetUnderAnimation]))
        
        // 횡 스크롤 애니메이션 설정
        for i: CGFloat in stride(from: CGFloat(0), to: needNumber, by: 1.0)
        {
            let sprite = SKSpriteNode(texture: under)
            sprite.zPosition = -50.0
            sprite.position = CGPoint(x: i * sprite.size.width, y: sprite.size.height / 2.0)
            sprite.run(repeatForeverUnderAnimation)
            baseNode.addChild(sprite)
        }
        
        // 상단 바위 이미지
        let above = SKTexture(imageNamed: "rock_above")
        above.filteringMode = .nearest
        
        // 화면 대비 텍스쳐 사이즈 기반으로 횡 스크롤링에 필요한 이미지 수 계산
        needNumber = 2.0 + (self.frame.size.width / above.size().width)
        
        // 횡 스크롤 애니메이션 구성
        let moveAboveAnimation = SKAction.moveBy(x: -above.size().width, y: 0.0, duration: TimeInterval(above.size().width / 20.0))
        let resetAboveAnimation = SKAction.moveBy(x: above.size().width, y: 0.0, duration: 0.0)
        let repeatForeverAboveAnimation = SKAction.repeatForever(SKAction.sequence([moveAboveAnimation, resetAboveAnimation]))
        
        // 횡 스크롤 애니메이션 설정
        for i: CGFloat in stride(from: CGFloat(0), to: needNumber, by: 1.0)
        {
            let sprite = SKSpriteNode(texture: above)
            sprite.zPosition = -50.0
            sprite.position = CGPoint(x: i * sprite.size.width, y: self.frame.size.height - (sprite.size.height / 2.0))
            sprite.run(repeatForeverAboveAnimation)
            baseNode.addChild(sprite)
        }
    }
    
    func setupCeilingAndLand()
    {
        let land = SKTexture(imageNamed: "land")
        land.filteringMode = .nearest
        
        var needNumber = 2.0 + (self.frame.size.width / land.size().width)
        
        let moveLandAnimation = SKAction.moveBy(x: -land.size().width, y: 0.0, duration: TimeInterval(land.size().width / 100.0))
        let resetLandAnimation = SKAction.moveBy(x: land.size().width, y: 0.0, duration: 0.0)
        let repeatForeverLandAnimation = SKAction.repeatForever(SKAction.sequence([moveLandAnimation, resetLandAnimation]))
        
        for i: CGFloat in stride(from: CGFloat(0), to: needNumber, by: 1.0)
        {
            let sprite = SKSpriteNode(texture: land)
            sprite.position = CGPoint(x: i * sprite.size.width, y: sprite.size.height / 2.0)
            
            // 물리 강체 설정
            sprite.physicsBody = SKPhysicsBody(texture: land, size: land.size())
            sprite.physicsBody?.isDynamic = false
            sprite.physicsBody?.categoryBitMask = ColliderType.World
            
            sprite.run(repeatForeverLandAnimation)
            baseNode.addChild(sprite)
        }
        
        let ceiling = SKTexture(imageNamed: "ceiling")
        ceiling.filteringMode = .nearest
        
        needNumber = 2.0 + (self.frame.size.width / ceiling.size().width)
        
        for i: CGFloat in stride(from: CGFloat(0), to: needNumber, by: 1.0)
        {
            let sprite = SKSpriteNode(texture: ceiling)
            sprite.position = CGPoint(x: i * sprite.size.width, y: self.frame.size.height - sprite.size.height / 2.0)
            
            sprite.physicsBody = SKPhysicsBody(texture: ceiling, size: ceiling.size())
            sprite.physicsBody?.isDynamic = false
            sprite.physicsBody?.categoryBitMask = ColliderType.World
            
            sprite.run(repeatForeverLandAnimation)
            baseNode.addChild(sprite)
        }
    }
    
    func setupPlayer()
    {
        // SKTexture 배열 지정
        var playerTexture = [SKTexture]()
        
        // 스프라이트 추가
        for imageName in Constants.PlayerImages
        {
            let texture = SKTexture(imageNamed: imageName)
            texture.filteringMode = .linear
            playerTexture.append(texture)
        }
        
        // 애니메이션 추가
        let playerAnimation = SKAction.animate(with: playerTexture, timePerFrame: 0.2)
        let loopAnimation = SKAction.repeatForever(playerAnimation)
        
        player = SKSpriteNode(texture: playerTexture[0])
        player.position = CGPoint(x: self.frame.size.width * 0.35, y: self.frame.size.height * 0.6)
        player.run(loopAnimation)
        
        // 물리 강체 추가
        player.physicsBody = SKPhysicsBody(texture: playerTexture[0], size: playerTexture[0].size())
        
        // 중력의 영향 받음
        player.physicsBody?.isDynamic = true
        player.physicsBody?.allowsRotation = false
        
        player.physicsBody?.categoryBitMask = ColliderType.Player;
        
        // 충돌 타겟 설정
        player.physicsBody?.collisionBitMask = ColliderType.World | ColliderType.Coral
        
        // SKPhysicsContactDelegate 콜백 호출 타겟 설정
        player.physicsBody?.contactTestBitMask = ColliderType.World | ColliderType.Coral
        
        self.addChild(player)
    }
    
    func setupCoral()
    {
        let coralUnder = SKTexture(imageNamed: "coral_under")
        coralUnder.filteringMode = .linear
        let coralAbove = SKTexture(imageNamed: "coral_above")
        coralAbove.filteringMode = .linear
        
        let distanceToMove = CGFloat(self.frame.size.width + 2.0 * coralUnder.size().width)
        
        let moveAnimation = SKAction.moveBy(x: -distanceToMove, y: 0.0, duration: TimeInterval(distanceToMove / 100.0))
        let removeAnimation = SKAction.removeFromParent()
        let coralAnimation = SKAction.sequence([moveAnimation, removeAnimation])
        
        let newCoralAnimation = SKAction.run(
        {
            let coral = SKNode()
            coral.position = CGPoint(x: self.frame.size.width + coralUnder.size().width * 2, y: 0.0)
            coral.zPosition = -50.0
            
            let height = UInt32(self.frame.size.height / 12)
            let y = CGFloat(arc4random_uniform(height * 2) + height)
            
            let under = SKSpriteNode(texture: coralUnder)
            under.position = CGPoint(x: 0.0, y: y)
            
            under.physicsBody = SKPhysicsBody(texture: coralUnder, size: under.size)
            under.physicsBody?.isDynamic = false
            under.physicsBody?.categoryBitMask = ColliderType.Coral
            under.physicsBody?.contactTestBitMask = ColliderType.Player
            coral.addChild(under)
            
            let above = SKSpriteNode(texture: coralAbove)
            above.position = CGPoint(x: 0.0, y: y + (under.size.height / 2.0) + 160.0 + (above.size.height / 2.0))
            
            above.physicsBody = SKPhysicsBody(texture: coralUnder, size: above.size)
            above.physicsBody?.isDynamic = false
            above.physicsBody?.categoryBitMask = ColliderType.Coral
            above.physicsBody?.contactTestBitMask = ColliderType.Player
            coral.addChild(above)
            
            let scoreNode = SKNode()
            scoreNode.position = CGPoint(x: (above.size.width / 2.0) + 5.0, y: self.frame.height / 2.0)
            
            // 화면 전체 세로길이(Height) 만큼 보이지 않는 충돌 박스 설정
            scoreNode.physicsBody = SKPhysicsBody(rectangleOf: CGSize(width: 10.0, height: self.frame.size.height))
            scoreNode.physicsBody?.isDynamic = false
            scoreNode.physicsBody?.categoryBitMask = ColliderType.Score
            scoreNode.physicsBody?.contactTestBitMask = ColliderType.Player
            coral.addChild(scoreNode)
            
            coral.run(coralAnimation)
            self.coralNode.addChild(coral)
        })
        
        let delayAnimation = SKAction.wait(forDuration: 2.5)
        let repeatforeverAnimation = SKAction.repeatForever(SKAction.sequence([newCoralAnimation, delayAnimation]))
        
        self.run(repeatforeverAnimation)
    }
    
    func setupScoreLabel()
    {
        scoreLabelNode = SKLabelNode(fontNamed: "Arial Bold")
        scoreLabelNode.fontColor = UIColor.black
        scoreLabelNode.position = CGPoint(x: self.frame.width / 2.0, y: self.frame.size.height * 0.9)
        scoreLabelNode.zPosition = 100.0
        scoreLabelNode.text = String(score!)
        
        self.addChild(scoreLabelNode)
    }
    
    func didBegin(_ contact: SKPhysicsContact)
    {
        if baseNode.speed <= 0.0
        {
            return
        }
        
        let rawScoreType = ColliderType.Score
        let rawNoneType = ColliderType.None
        
        // 점수 판정 라인과 충돌
        if (contact.bodyA.categoryBitMask & rawScoreType) == rawScoreType
        || (contact.bodyB.categoryBitMask & rawScoreType) == rawScoreType
        {
            score = score + 1
            scoreLabelNode.text = String(score!)
            
            // 점수 연출효과 애니메이션
            let scaleUpAnimation = SKAction.scale(to: 1.5, duration: 0.1)
            let scaleDownAnimation = SKAction.scale(to: 1.0, duration: 0.1)
            scoreLabelNode.run(SKAction.sequence([scaleUpAnimation, scaleDownAnimation]))
            
            // 충돌 초기화
            if (contact.bodyA.categoryBitMask & rawScoreType) == rawScoreType
            {
                contact.bodyA.categoryBitMask = ColliderType.None
                contact.bodyA.contactTestBitMask = ColliderType.None
            }
            else
            {
                contact.bodyB.categoryBitMask = ColliderType.None
                contact.bodyB.contactTestBitMask = ColliderType.None
            }
        }
        else if (contact.bodyA.categoryBitMask & rawScoreType) == rawNoneType
             || (contact.bodyB.categoryBitMask & rawScoreType) == rawNoneType
        {
            // 아무 것도 하지 않음
        }
        else
        {
            // baseNode에 걸려 있던 모든 애니메이션 정지
            baseNode.speed = 0.0
            
            player.physicsBody?.collisionBitMask = ColliderType.World
            let rolling = SKAction.rotate(byAngle: CGFloat(M_PI) * player.position.y * 0.01, duration: 1.0)
            player.run(rolling, completion:
            {
                // 회전 애니메이션이 끝나면 애니메이션 정지
                self.player.speed = 0.0
            })
        }
    }
    
    override func didMove(to view: SKView)
    {
        // 멤버 변수 초기화
        score = 0
        
        // 중력 추가
        self.physicsWorld.gravity = CGVector(dx: 0.0, dy: -2.0)
        self.physicsWorld.contactDelegate = self
        
        // 최상위 루트 노드 생성
        baseNode = SKNode()
        baseNode.speed = 1.0
        self.addChild(baseNode)
        
        coralNode = SKNode()
        baseNode.addChild(coralNode)
        
        self.setupBackgroundSea()
        self.setupBackgroundRock()
        self.setupCeilingAndLand()
        
        // 플레이어 캐릭터 세팅
        self.setupPlayer()
        
        self.setupCoral()
        self.setupScoreLabel()
    }
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?)
    {
        if 0.0 < baseNode.speed
        {
            for touch: AnyObject in touches
            {
                _ = touch.location(in: self)
                
                // 중력을 0으로 만들고
                player.physicsBody?.velocity = CGVector.zero
                
                // 힘 작용
                player.physicsBody?.applyImpulse(CGVector(dx: 0.0, dy: 23.0))
            }
        }
        else if 0.0 == baseNode.speed && 0.0 == player.speed
        {
            // 초기화
            coralNode.removeAllChildren()
            
            score = 0;
            scoreLabelNode.text = String(score!)
            
            // 플레이어 초기화
            player.position = CGPoint(x: self.frame.size.width * 0.35, y: self.frame.size.height * 0.6)
            player.physicsBody?.velocity = CGVector.zero
            player.physicsBody?.collisionBitMask = ColliderType.World | ColliderType.Coral
            player.zRotation = 0.0
            
            // 다시 시작
            player.speed = 1.0
            baseNode.speed = 1.0
        }
    }
   
    override func update(_ currentTime: TimeInterval) {

    }
}

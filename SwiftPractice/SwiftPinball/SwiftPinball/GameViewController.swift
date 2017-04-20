//
//  GameViewController.swift
//  SwiftPinball
//
//  Created by zrma on 2016. 3. 25..
//  Copyright (c) 2016년 zrma. All rights reserved.
//

import UIKit
import SpriteKit

class GameViewController: UIViewController
{
    override func viewDidLoad()
    {
        super.viewDidLoad()

        let scene = GameScene()
        
        let skView = self.view as! SKView
        skView.showsFPS = true
        skView.showsNodeCount = true
        
        /* Sprite Kit applies additional optimizations to improve rendering performance */
        skView.ignoresSiblingOrder = false
        
        /* Set the scale mode to scale to fit the window */
        scene.scaleMode = .aspectFill
        scene.size = skView.frame.size
        
        skView.presentScene(scene)
        
        // 멀티터치 금지
        // view.multipleTouchEnabled = false
    }

    override var shouldAutorotate: Bool {
        return false
    }
    
    override var supportedInterfaceOrientations: UIInterfaceOrientationMask {
        if UIDevice.current.userInterfaceIdiom == .phone {
            return .allButUpsideDown
        } else {
            return .all
        }
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Release any cached data, images, etc that aren't in use.
    }

    override var prefersStatusBarHidden: Bool {
        return true
    }
}

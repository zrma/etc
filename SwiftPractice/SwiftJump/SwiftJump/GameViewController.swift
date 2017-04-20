//
//  GameViewController.swift
//  SwiftJump
//
//  Created by zrma on 2016. 12. 7..
//  Copyright © 2016년 zrma. All rights reserved.
//

import UIKit
import SpriteKit
import GameplayKit

class GameViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        
        let scene = GameScene()
        
        let view = self.view as! SKView
        
        view.showsFPS = true
        view.showsNodeCount = true
        view.ignoresSiblingOrder = true
        
        scene.size = view.frame.size
        
        view.presentScene(scene)
    }

    override var shouldAutorotate: Bool {
        return true
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

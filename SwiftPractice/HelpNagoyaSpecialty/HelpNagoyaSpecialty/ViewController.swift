//
//  ViewController.swift
//  HelpNagoyaSpecialty
//
//  Created by zrma on 2016. 2. 11..
//  Copyright © 2016년 zrma. All rights reserved.
//

import UIKit
import SpriteKit

class ViewController: UIViewController {
    override func viewDidLoad() {
        super.viewDidLoad()

        // 씬 작성
        let scene = GameScene()
        let view = self.view as! SKView
        
        view.showsFPS = true
        view.showsNodeCount = true
        
        scene.size = view.frame.size
        
        // 뷰어에 씬 표시
        view.presentScene(scene)
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}


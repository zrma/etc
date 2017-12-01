using System;
using System.Collections.Generic;

#if __IOS__
using UIKit;
using SKColor = UIKit.UIColor;
#else
using AppKit;
using SKColor = AppKit.NSColor;
#endif

using CoreAnimation;
using CoreGraphics;
using Foundation;
using SceneKit;

namespace test
{
    [Register("GameViewController")]
#if __IOS__
	public class GameViewController : UIViewController
#else
    public class GameViewController : NSViewController
#endif
    {
        public GameViewController(IntPtr handle) : base(handle)
        {
        }

#if __IOS__
		public override void ViewDidLoad ()
		{
			base.ViewDidLoad ();
			Setup ();
		}
#else
        public override void AwakeFromNib()
        {
            base.AwakeFromNib();
            Setup();
        }
#endif

        void Setup()
        {
            // create a new scene
            var scene = SCNScene.FromFile("art.scnassets/ship");

            // create and add a camera to the scene
            var cameraNode = SCNNode.Create();
            cameraNode.Camera = SCNCamera.Create();
            scene.RootNode.AddChildNode(cameraNode);

            // place the camera
            cameraNode.Position = new SCNVector3(0, 0, 15);

            // create and add a light to the scene
            var lightNode = SCNNode.Create();
            lightNode.Light = SCNLight.Create();
            lightNode.Light.LightType = SCNLightType.Omni;
            lightNode.Position = new SCNVector3(0, 10, 10);
            scene.RootNode.AddChildNode(lightNode);

            // create and add an ambient light to the scene
            var ambientLightNode = SCNNode.Create();
            ambientLightNode.Light = SCNLight.Create();
            ambientLightNode.Light.LightType = SCNLightType.Ambient;
            ambientLightNode.Light.Color = SKColor.DarkGray;
            scene.RootNode.AddChildNode(ambientLightNode);

            // retrieve the ship node
            var ship = scene.RootNode.FindChildNode("ship", true);

            // animate the 3d object
#if __IOS__
			ship.RunAction (SCNAction.RepeatActionForever (SCNAction.RotateBy (0, 2, 0, 1)));
#else
            var animation = CABasicAnimation.FromKeyPath("rotation");
            animation.To = NSValue.FromVector(new SCNVector4(0, 1, 0, NMath.PI * 2));
            animation.Duration = 3;
            animation.RepeatCount = float.MaxValue; //repeat forever
            ship.AddAnimation(animation, null);
#endif

            // retrieve the SCNView
            var scnView = (SCNView)View;

            // set the scene to the view
            scnView.Scene = scene;

            // allows the user to manipulate the camera
            scnView.AllowsCameraControl = true;

            // show statistics such as fps and timing information
            scnView.ShowsStatistics = true;

            // configure the view
            scnView.BackgroundColor = SKColor.Black;

#if __IOS__
			// add a tap gesture recognizer
			var tapGesture = new UITapGestureRecognizer (HandleTap);
			var gestureRecognizers = new List<UIGestureRecognizer> ();
			gestureRecognizers.Add (tapGesture);
			gestureRecognizers.AddRange (scnView.GestureRecognizers);
			scnView.GestureRecognizers = gestureRecognizers.ToArray ();
#endif
        }

#if __IOS__
		void HandleTap (UIGestureRecognizer gestureRecognize)
		{
			// retrieve the SCNView
			var scnView = (SCNView)View;

			// check what nodes are tapped
			CGPoint p = gestureRecognize.LocationInView (scnView);
			SCNHitTestResult[] hitResults = scnView.HitTest (p, (SCNHitTestOptions)null);

			// check that we clicked on at least one object
			if (hitResults.Length > 0) {
				// retrieved the first clicked object
				SCNHitTestResult result = hitResults [0];

				// get its material
				SCNMaterial material = result.Node.Geometry.FirstMaterial;

				// highlight it
				SCNTransaction.Begin ();
				SCNTransaction.AnimationDuration = 0.5f;

				// on completion - unhighlight
				SCNTransaction.SetCompletionBlock (() => {
					SCNTransaction.Begin ();
					SCNTransaction.AnimationDuration = 0.5f;

					material.Emission.Contents = UIColor.Black;

					SCNTransaction.Commit ();
				});

				material.Emission.Contents = UIColor.Red;

				SCNTransaction.Commit ();
			}
		}

		public override bool ShouldAutorotate ()
		{
			return true;
		}

		public override UIInterfaceOrientationMask GetSupportedInterfaceOrientations ()
		{
			return UIInterfaceOrientationMask.AllButUpsideDown;
		}
#endif
    }
}


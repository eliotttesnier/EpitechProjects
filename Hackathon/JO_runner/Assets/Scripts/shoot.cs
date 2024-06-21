using UnityEngine;
using System.Collections;
public class ShootDemo : MonoBehaviour {
    public Rigidbody projectile;
    public float speed = 75;

    // Update is called once per frame

    void Update () {
        if (Input.GetKey(KeyCode.E)) {
            Rigidbody instantiatedProjectile = Instantiate(projectile,
                                                           transform.position,
                                                           transform.rotation)
                as Rigidbody;
            instantiatedProjectile.velocity = transform.TransformDirection(new Vector3(0, 0,speed));
        }
    }
}

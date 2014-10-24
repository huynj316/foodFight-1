using UnityEngine;
using System.Collections;

public class TenPrint : MonoBehaviour {
	
	public Transform originalBlueprint;
	public Transform Blueprint;
	public AudioClip box;

	void Start () {

		StartCoroutine (TenPrintProcess());//coroutine can stop at points
	}
	
	// Update is called once per frame // will happen continually
//	void Update () { //"gluing strings together" = concatenation
	IEnumerator TenPrintProcess () {
		int cubeSoFar = 0; // how many characters I've printed so far in this line
		float x = 0;
		float y = 0;
		float z = 0;

		while (true) {
			//flip virtual coin, if heads print \ if tales print /
			if(Random.Range(0f,10f)<5f){ //5 give equal probability
				Instantiate (originalBlueprint, new Vector3(x,0,0), 45);
				x++;
				cubeSoFar++;
				audio.PlayOneShot (box);

			} else {
				Instantiate (Blueprint, new Vector3(0,0,z), Random.rotation);
				z++;
			}
				cubeSoFar++;
			if (cubeSoFar >= 10) { //after 10 slashes
				Instantiate (originalBlueprint, new Vector3(0,y,0), Random.rotation);
				y++;
				cubeSoFar = 0;
				}
			yield return new WaitForSeconds(0.1f); //tell unity to take a break
			
		}
	}
}
